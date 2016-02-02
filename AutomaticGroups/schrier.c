#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
//#include <conio.h>

const char *genstring = "generatorOrder";
const char *invstring = "inverses";
const char *relstring = "equations";

typedef struct cosettag {               
	int CloserCoset;        // The index of the next closer coset to the identity
				// or -1 if the coset _is_ the identity.
	int GenBack;            // The index of the generator pointing back to the 
				// identity; or 0 if the coset _is_ the identity.
	int *Generator;         // Length numgens array of coset pointers
	int *Inverse;           // Length numgens array of coset pointers
	int *Representative;    // Array of length < INDEX, consisting of the path
				// from the identity to this coset
	int RepLength;          // Length of the array 'rep'
	} CosetType;

typedef struct graphtag {
	int Index;              // Number of cosets
	int NumGens;            // Number of generators; same for all cosets in graph
	CosetType *Coset;       // Array of index cosets
	} CosetGraph;

typedef struct pres_tag {
	char **GenLabel;        // An array of strings containing the generator symbols
	char **InvLabel;        // An array of strings containing the inverse symbols
	int NumGens;            // The number of generators/inverses
	
	char **Relators;        // An array of strings containing the relator symbols
	int NumRels;            // The number of relators
	} Presentation;


#define MAXLINE 200     /* maximum length of a line */

/*
Action on the data structure:
	Create the generators for the subgroup. 
		These are formed for each pair (s,g), where s is a coset representative and
		g is a generator of the group G. Travel along s, then apply g.  Now travel back
		along the tree to the identity.  The word formed in this way is a generator of 
		the subgroup.  Note that if applying g travelled along the tree, then the entire
		word was within the tree, and hence is trivial since travelling back to the 
		identity cancels s followed by g.

	Create the words for the relations.
		These are formed for each pair (s,R), where s is a coset representative and
		R is a relator of the group G.  They are conjugates of R by s, or sRS, where
		S is the INVERTED form of s.  That is, reverse the order of the generators 
		and switch uppercase with lowercase.

		Again, output these in Tex format.

	Represent the relations in terms of the (s,g) words.
		Given a (sRS) relation, follow along the word until you leave the tree.
		From the current vertex, insert the path back to the identity followed by the path
		back to the current vertex.  The string through the return to the identity will 
		be a (s,g) generator, or its inverse.  
			Determine which one and output this information.
		Now examine the new word beginning at the identity and follow the same procedure.
		Continue until the word is empty.

Output file : an ascii file, that consists of the Schrier
(s) coset representatives, the (s,g) subgroup generators, the (sRS) relations of the 
subgroup, and the (sRS) relations written in terms of the (s,g) generators.
*/

void usage(void);

int gen_inverse( int gen )
{
	return (-1*gen);
}

int getcosetinfo(FILE *cosfile, int num, CosetGraph *CG)
{
	// file format:
	// Assume a group with n generators, 1, ..., numgens
	// No dependency on generator names; 
	// Cosets and generators are referred to by number
	// index
	// m rows of n+2 integers
	// The first n are coset where the j-th generator takes the i-th coset
	// The next is the coset that is closer to the identity coset, or -1 if
	// the coset _is_ the identity
	// The next is the generator taking the coset closer to the identity
	// and is negative if it is via the inverse.  
	// It is 0 if the coset is the identity
	int counter, cos_counter, gen_counter, intin, n, i;

	n = fscanf(cosfile, "%d", &intin);
	if ( n == EOF )
	{
		fprintf(stdout, "The coset file should start with an integer.\n");
		return (1);
	}
	CG->Index = intin;
	// Allocate space for coset array
	CG->Coset = (CosetType *) calloc(CG->Index, sizeof(CosetType));
	if (CG->Coset == NULL)
	{
		fprintf(stdout, "Unable to allocate memory for coset table.\n");
		return (1);
	}
	
	// Copy the number of generators
	
	CG->NumGens = num;
	// Do cosets
	for (cos_counter = 0; cos_counter < CG->Index; cos_counter++)
	{
		// allocate space for this coset data
		CG->Coset[cos_counter].Generator = (int *)calloc(CG->NumGens, sizeof(int));
		if (CG->Coset[cos_counter].Generator == NULL)
		{
			fprintf(stdout, "Unable to allocate memory for %d-th coset generator labels.\n", cos_counter);
			return (1);
		}
		CG->Coset[cos_counter].Inverse = (int *)calloc(CG->NumGens, sizeof(int));
		if (CG->Coset[cos_counter].Inverse == NULL)
		{
			fprintf(stdout, "Unable to allocate memory for %d-th coset inverse labels.\n", cos_counter);
			return (1);
		}
		// read coset data into arrays
#ifdef _DEBUG
		fprintf(stdout, "Reading coset %d data into arrays.\n", cos_counter);
#endif
		fprintf(stdout, "Coset %d Inverse = %p\n", cos_counter, CG->Coset[cos_counter].Inverse);

		for (gen_counter = 0; gen_counter < CG->NumGens; gen_counter++)
		{
			n = fscanf(cosfile, "%d", &intin);
			if (n == EOF)
			{
				fprintf(stdout, "Unable to read %d-th coset, %d-th generator.\n", cos_counter, gen_counter);
				return (1);
			}
#ifdef _DEBUG
			fprintf(stdout, "Read %d.  ", intin);
#endif
			CG->Coset[cos_counter].Generator[gen_counter] = intin;
#ifdef _DEBUG
			fprintf(stdout, "Coset %d times generator %d equals coset %d\n", cos_counter, gen_counter,intin);
#endif
			// add corresponding inverse information
			fprintf(stdout, "The address of Coset %d Inverse %d = %p\n", intin, gen_counter, &(CG->Coset[intin].Inverse[gen_counter]));
//			CG->Coset[intin].Inverse[gen_counter] = cos_counter;
#ifdef _DEBUG
			fprintf(stdout, "Therefore, coset %d times generator %d inverse equals coset %d\n", intin, gen_counter, cos_counter);
#endif
		}

		// now get closer coset
		n = fscanf(cosfile, "%d", &intin);
		if (n == EOF)
		{
			fprintf(stdout, "Unable to read %d-th coset, next closer coset.\n", cos_counter);
			return(1); 
		}
		CG->Coset[cos_counter].CloserCoset = intin;

		// now get generator back
		n = fscanf(cosfile, "%d", &intin);
		if (n == EOF)
		{
			fprintf(stdout, "Unable to read %d-th coset, generator back.\n", cos_counter);
			return(1); 
		}
		CG->Coset[cos_counter].GenBack = intin;
	}

	return(0);

#ifdef _DEBUG
	fprintf(stdout, "Determining paths to identity.\n");
#endif
	// Now that all data is read, determine the path to the identity.
	for ( cos_counter = 0; cos_counter < CG->Index; cos_counter++)
	{
#ifdef _DEBUG
		fprintf(stdout, "Pre-compute length of %d-th coset representative.\n", cos_counter);
#endif
		// determine the length of the path back
		CG->Coset[cos_counter].RepLength = 0;
		counter = cos_counter;
		while ( counter ) // Not at the identity coset
		{
#ifdef _DEBUG
			fprintf(stdout, "At %d-th coset, the next closer coset is %d.\n", counter, CG->Coset[counter].CloserCoset);
#endif
			counter = CG->Coset[counter].CloserCoset;
			CG->Coset[cos_counter].RepLength++;
		}
#ifdef _DEBUG
		fprintf(stdout, "The length is %d\n", CG->Coset[cos_counter].RepLength);
#endif
		
		CG->Coset[cos_counter].Representative = NULL;
		// allocate that much space, if there *is* a path to save
		if ( CG->Coset[cos_counter].RepLength )
		{
			CG->Coset[cos_counter].Representative = (int *)calloc( CG->Coset[cos_counter].RepLength, sizeof(int) );
			if ( CG->Coset[cos_counter].Representative == NULL )
			{
				fprintf(stdout, "Unable to allocate space for the %d-th coset representative.\n", cos_counter);
				return (1);
			}
			// retrace the path back, entering in reverse order
			i = CG->Coset[cos_counter].RepLength;
			counter = cos_counter;
			while (counter)
			{
				i--;    // since we started with the length of the array
#ifdef _DEBUG
				fprintf(stdout, "Representative[%d] = %d\n", i, gen_inverse(CG->Coset[counter].GenBack));
#endif
				CG->Coset[cos_counter].Representative[i] = gen_inverse(CG->Coset[counter].GenBack);
				// add inverse generator, since we're tracing backwards
				counter = CG->Coset[counter].CloserCoset;
				// move to next closer coset
			}
		}
	}
	return (0);
}

int getgroupinfo(FILE *gpfile, Presentation *GP)
{
	// returns 0 if no errors
	// non-zero otherwise
	char line[MAXLINE];
	int n, i, count;
	char ch;
	long position;  // store the file position of '['
	
	// find "generatorOrder := ["
	// Count number of commas to ']'
	// return number + 1
	// Errors: 
	// no ":=" after "generatorOrder"
	// no '[' after ":="
	// no ']'

	// Assume the input file is reset to the beginning
	// This should skip anything until it finds a string that matches 
	// "generatorOrder", and should stop at the end of the file
#ifdef _DEBUG
	printf("Counting generators\n");
	printf("Looking for %s\n", genstring);
#endif
	do
	{
		n = fscanf(gpfile, "%s", line);
	}
	while (n != EOF && strcmp(line, genstring));

	if (n == EOF)
	{
		fprintf(stdout, "Reached end of file before %s found.\n", genstring);
		return (1);
	}
#ifdef _DEBUG
	printf("Looking for :=\n");
#endif
	n = fscanf(gpfile, "%s", line);

	if (n == EOF)
	{
		fprintf(stdout,"Reached end of file before ':=' found.\n");
		return (1);
	}

	if (strcmp(line, ":="))
	{
		fprintf(stdout, "Syntax error in group file. %s must be followed by ':=', not %s.\n", genstring, line);
		return (1);
	}
#ifdef _DEBUG
	printf("Looking for [\n");
#endif
	do
		n = fscanf(gpfile, "%c", &ch);
	while (n != EOF && isspace(ch));        // skip spaces
	
	if (n == EOF)
	{
		fprintf(stdout, "Reached end of file before '[' found.\n");
		return (1);
	}
	
	if (ch != '[')
	{
		fprintf(stdout, "Syntax error in group file. ':=' must be followed by '[', not %c.\n", ch);
		return (1);
	}
	
	position = ftell(gpfile);       // save position of beginning of generators
	
	// Count the number of commas (',') before ']'
	GP->NumGens = 1;
	do
	{
		n = fscanf(gpfile, "%c", &ch);
		if (ch == ',')
			GP->NumGens++;  // count the commas
	}
	while (n != EOF && (ch != ']'));

	if (n == EOF)
	{
		fprintf(stdout,"Reached end of file before ']' found.\n");
		return (1);
	}
	// The number of generators is gencount
	GP->GenLabel = (char**) calloc(GP->NumGens, sizeof(char*));
	GP->InvLabel = (char**) calloc(GP->NumGens, sizeof(char*));

	// Go to where the generator started
	fseek(gpfile, position, _SEEK_SET);
	
	for (i = 0; i < GP->NumGens; i++)
	{       
#ifdef _DEBUG
		printf("Processing %d-th generator.\n", i);
		printf("\tCounting length. ");
#endif
		count = 0;
		do
		{
			n = fscanf(gpfile, "%c", &ch);
#ifdef _DEBUG
			printf("%c",ch);
#endif
			count++; 
		}
		while (n != EOF && (ch != ',') && (ch != ']') && !isspace(ch) );

		if (n == EOF)
		{
			fprintf(stdout, "SCHRIER ERROR: group file ended before %d-th generator.\n", i);
			return (1);
		}
#ifdef _DEBUG
		printf("\n\tGenerator %d is %d characters long.\n", i, count-1);
#endif
		GP->GenLabel[i] = (char*)malloc( count );
		if (GP->GenLabel[i] == NULL)
		{
			fprintf(stdout, "Unable to allocate space for %d-th generator.\n", i);
			return (1);
		}
		// return back to start of generator
		fseek(gpfile, position, SEEK_SET);
		fread(GP->GenLabel[i], 1, (size_t)count-1, gpfile);
		GP->GenLabel[i][count-1] = '\0';
#ifdef _DEBUG
		printf("\tRead in %s\n", GP->GenLabel[i]);
#endif
		// now move to the beginning of the next generator
		do
			n = fscanf(gpfile, "%c", &ch);
		while (n != EOF && ( (ch == ',') || isspace(ch) ) );
		
		if (n == EOF)
		{
			fprintf(stdout, "SCHRIER ERROR: group file ended before %d-th generator.\n", i+1);
			return (1);
		}
		// back up one character
		fseek(gpfile, -1L, SEEK_CUR);
		position = ftell(gpfile);
	}
	
	// Now do inverses
	rewind(gpfile);

#ifdef _DEBUG
	printf("Counting inverses\n");
	printf("Looking for %s\n", invstring);
#endif
	do
	{
		n = fscanf(gpfile, "%s", line);
	}
	while (n != EOF && strcmp(line, invstring));

	if (n == EOF)
	{
		fprintf(stdout, "Reached end of file before %s found.\n", invstring);
		return (1);
	}
#ifdef _DEBUG
	printf("Looking for :=\n");
#endif
	n = fscanf(gpfile, "%s", line);

	if (n == EOF)
	{
		fprintf(stdout, "Reached end of file before ':=' found.\n");
		return (1);
	}

	if (strcmp(line, ":="))
	{
		fprintf(stdout, "Syntax error in group file. %s must be followed by ':=', not %s.\n", invstring, line);
		return (1);
	}

#ifdef _DEBUG
	printf("Looking for [\n");
#endif
	do
		n = fscanf(gpfile, "%c", &ch);
	while (n != EOF && isspace(ch));        // skip spaces
	
	if (n == EOF)
	{
		fprintf(stdout, "Reached end of file before '[' found.\n");
		return (1);
	}
	
	if (ch != '[')
	{
		fprintf(stdout, "Syntax error in group file. ':=' must be followed by '[', not %c.\n", ch);
		return (1);
	}
	
	position = ftell(gpfile);       // save position of beginning of inverses
	
	// Count the number of commas (',') before ']'
	count = 1;
	do
	{
		n = fscanf(gpfile, "%c", &ch);
		if (ch == ',')
			count++;        // count the commas
	}
	while (n != EOF && (ch != ']'));

	if (n == EOF)
	{
		fprintf(stdout, "Reached end of file before ']' found.\n");
		return (1);
	}
	// The number of generators is gencount
	if ( GP->NumGens != count )
	{
		fprintf(stdout, "The number of inverses, %d, is different from the number of generators, %d\n", count, GP->NumGens);
		return(1);
	}

	// Go to where the inverse started
	fseek(gpfile, position, SEEK_SET);
	
	for (i = 0; i < GP->NumGens; i++)
	{       
#ifdef _DEBUG
		printf("Processing %d-th inverse.\n", i);
		printf("\tCounting length. ");
#endif
		count = 0;
		do
		{
			n = fscanf(gpfile, "%c", &ch);
#ifdef _DEBUG
			printf("%c",ch);
#endif
			count++; 
		}
		while (n != EOF && (ch != ',') && (ch != ']') && !isspace(ch) );

		if (n == EOF)
		{
			fprintf(stdout, "SCHRIER ERROR: group file ended before %d-th inverse.\n", i);
			return (1);
		}
#ifdef _DEBUG
		printf("\n\tInverse %d is %d characters long.\n", i, count-1);
#endif
		GP->InvLabel[i] = (char*)malloc( count );
		if (GP->InvLabel[i] == NULL)
		{
			fprintf(stdout, "Unable to allocate space for %d-th inverse.\n", i);
			return (1);
		}
		// return back to start of generator
		fseek(gpfile, position, SEEK_SET);
		fread(GP->InvLabel[i], 1, (size_t)count-1, gpfile);
		GP->InvLabel[i][count-1] = '\0';
#ifdef _DEBUG
		printf("\tRead in %s\n", GP->InvLabel[i]);
#endif
		// now move to the beginning of the next generator
		do
			n = fscanf(gpfile, "%c", &ch);
		while (n != EOF && ( (ch == ',') || isspace(ch) ) );
		
		if (n == EOF)
		{
			fprintf(stdout, "SCHRIER ERROR: group file ended before %d-th inverse.\n", i+1);
			return (1);
		}
		// back up one character
		fseek(gpfile, -1L, SEEK_CUR);
		position = ftell(gpfile);
	}
	// Now do relators
	return (0);
}

void fprintrep( FILE *outfile,          
		const Presentation *GP, const CosetGraph *CG,   
		int CS,                 const char *sep)
{
	// print the coset representative to the given file, with 'sep' in between
	// generators.
	// Need presentation for the generator and inverse labels
	int i;
	
	if (!CG->Coset[CS].RepLength)   // identity coset
	{
		fprintf(outfile, "1");
		return;
	}
	// Do the 0-th one without a preceding 'sep'
	// The -1 is since the generator numbers are not 0 based
	if (CG->Coset[CS].Representative[0] > 0)
		fprintf(outfile, "%s", GP->GenLabel[CG->Coset[CS].Representative[0]-1]);
	else
		fprintf(outfile, "%s", GP->InvLabel[-CG->Coset[CS].Representative[0]-1]);
	
	for (i = 1; i < CG->Coset[CS].RepLength; i++)
	{
		fprintf(outfile, "%s", sep);
		if (CG->Coset[CS].Representative[i] > 0)
			fprintf(outfile, "%s", GP->GenLabel[CG->Coset[CS].Representative[i]-1]);
		else
			fprintf(outfile, "%s", GP->InvLabel[-CG->Coset[CS].Representative[i]-1]);
	}
}

void fprintpathback(FILE *outfile, 
		const Presentation *GP, const CosetGraph *CG,   
		int CS,                 const char *sep)
{
	// print the path back to the identity to the given file, with 'sep' in between
	// generators.
	// Need presentation for the generator and inverse labels
	if (!CS)        // CS == 0 is the identity coset
	{
		fprintf(outfile, "1");
		return;
	}
	
	if ( CG->Coset[CS].GenBack > 0 )
		fprintf(outfile, "%s", GP->GenLabel[CG->Coset[CS].GenBack - 1] );
	else
		fprintf(outfile, "%s", GP->InvLabel[-CG->Coset[CS].GenBack - 1] );

	CS = CG->Coset[CS].CloserCoset;
	while (CS)      // not the identity coset
	{
		if ( CG->Coset[CS].GenBack > 0 )
			fprintf(outfile, "%s%s", sep, GP->GenLabel[CG->Coset[CS].GenBack - 1] );
		else
			fprintf(outfile, "%s%s", sep, GP->InvLabel[-CG->Coset[CS].GenBack - 1] );
		CS = CG->Coset[CS].CloserCoset;
	}
}

int isSchrier(const CosetGraph *CG, int cos_start, int gen)
{
	// returns 1 if the representative to CG->Coset[cos_start] plus the outgoing generator 
	// gen from CG->Coset[cos_start] is the Schrier representative for the new coset.
	
	// Returns 0 if gen is a valid generator number, but if the representative
	// to CG->Coset[cos_start] plus the outgoing generator gen from 
	// CG->Coset[cos_start] is not the Schrier representative for the new coset.

	int cos_dest;
	
	assert( abs(gen) <= CG->NumGens ); // abs(gen) must be less than or equal to the number of generators.
	assert (gen != 0);	// gen must be non-zero, since -gen is its inverse

	// Go to the destination coset
	if (gen > 0)
		cos_dest = CG->Coset[cos_start].Generator[gen-1];
	else
		cos_dest = CG->Coset[cos_start].Inverse[-gen-1];
	
	// Did you get there via an edge in the Schrier tree?
	if ( CG->Coset[cos_dest].GenBack == gen_inverse(gen) )  // we invert, since this is `looking backwards'
		return (1);
	else
		return (0);
}

void main(argc, argv)
int argc;
char *argv[];
{
	/*
	Input file structure:
	First integer = index
	
	Relator file structure:
	generatorOrder := [,,,],
	inverses := [,,,],
	equations := 
	[
		[ * * * , * * * * *],
		[ * * *  * , * * * *]
	]
	Generators are given as a comma-separated list of symbols, surrounded by
	square brackets.  A comma fol
	NUMGEN symbols are generator symbols.
	Next NUMGEN symbols are corresponding inverse symbols.
	Remaining data is relators
	This file consists of lines of integers separated by white space with 
	one line for each relator of the group G. 
	The first integer on a line says how many other integers are following on
	that line.

	If the generators are g_{1},...,g_{NUMGENS}, the integers on the lines
	are the non-zero integers from -NUMGENS to NUMGENS, with negative
	numbers for inverse generators in the relator.
		
	Output file structure:
	Ascii file, that 
	consists of the Schrier (s) coset representatives, the (s,g) 
	subgroup generators, the (sRS) relations of the subgroup, and 
	the (sRS) relations written in terms of the (s,g) generators.
*/

	FILE    *cosetfile;     /* Following Input file structure criteria above. */
	FILE    *groupfile;     /* Following Relator file structure criteria above. */
	FILE    *outfile;       /* Following Output file structure criteria above. */
	int     output;         /* TRUE if output is to a file, FALSE if to stdout */
	CosetGraph      Graph;  // The global coset variable
	Presentation    Group;  // The global group variable


	int     i,j;            /* index counters for arrays, etc. */

// Check for proper usage
	if (argc < 3) // need a coset file, relator file, optional output file
	{
		usage();
		exit(0);
	}
	
	/* argc >= 3 */
// Try to open files
	// Try to open coset file
	cosetfile = fopen(argv[1],"r");
	if (cosetfile)
		fprintf(stdout,"SCHRIER: Opened file %s\n", argv[1]);
	else
	{
		fprintf(stdout,"SCHRIER error: Unable to open coset file %s.\n", argv[1]);
		exit(1);
	}

	// Try to open group data file
	groupfile = fopen(argv[2],"r");
	if (!groupfile)
	{
		fprintf(stdout,"Unable to open group data file %s\n",argv[2]);
		fclose(cosetfile);
		exit(0);
	}

	// Set output file or stdout for output
	if (argc > 3)
	{
		outfile = fopen(argv[3], "w");

		if (outfile)
		{
			fprintf(stdout,"SCHRIER: Opened output file %s\n", argv[3]);
			output = 1;
		}
		else
		{
			fprintf(stdout,"SCHRIER: Unable to open selected input file %s\nUsing stdout.\n", argv[3]);
			outfile = stdout;
			output = 0;                     
		}
	}
	else    // no output file specified, so try stdout
	{
		outfile = stdout;
		output = 0;
	}

// Try to read data files into memory
	// Try group file
	if (getgroupinfo(groupfile, &Group))
	{
		fprintf(stdout, "SCHRIER: Error in getgroupinfo, on file %s\n", argv[2]);
		fclose(groupfile);
		fclose(cosetfile);
		if (output)
			fclose(outfile);
		exit(1);
	}
	// Try coset file
	if (getcosetinfo(cosetfile, Group.NumGens, &Graph))
	{
		fprintf(stdout, "SCHRIER: Error in getcosetinfo, on file %s\n", argv[1]);
		fclose(groupfile);
		fclose(cosetfile);
		if (output)
			fclose(outfile);
		exit(1);
	}
	exit(0);
/*
Coset file format:
The first row consists of one integer, the index of the subgroup, INDEX.
The next INDEX rows contain the coset multiplication data; in the form of the 
separated by white space
The 1-st, ..., NUMGENS-th columns contain the coset number
where the corresponding generator takes the given coset.

Coset operations:
* Given a coset, Hg, and a generator, x, I want to know the coset that is the product
  Hgx.
* Given a coset, Hg, I want to know if it is the identity coset, H.
* Given a coset, I want to know the next closest coset to the identity.
* This will lead to a routine that returns the path back to the identity
* and a routine that returns the path from the identity to a given coset
* Given a coset, I want to know the generator that takes me to the next closest coset
  to the identity.

Coset data structure:
* Multiplying coset[i] by generator[j] ends up at coset[i].generator[j]
* The next closest coset to the identity coset from coset[i] is coset[i].nextclosest
* The generator (or inverse) that takes coset[i] closer to the identity coset is
  coset[i].genback.  If coset[i].genback is negative, it is the inverse generator.
* If i == 0, then coset[i] is the identity and vice-versa.

*/
	// Diagnostic: Output the raw data:
	fprintf(outfile, "Raw Data\nNumber of cosets: %d\nNumber of Generators: %d\n", Graph.Index, Graph.NumGens);
	for (i = 0; i < Graph.Index; i++)
	{
		fprintf(outfile, "Coset %d\nNeigbors by generators\n", i);
		for (j = 0; j < Graph.NumGens; j++)
			fprintf(outfile, "%d ", Graph.Coset[i].Generator[j] );
		fprintf(outfile, "\nNeighbors by inverses\n");
		for (j = 0; j < Graph.NumGens; j++)
			fprintf(outfile, "%d ", Graph.Coset[i].Inverse[j]);
		fprintf(outfile, "\nCloserCoset: %d\nGenerator Back: %d\n", Graph.Coset[i].CloserCoset, Graph.Coset[i].GenBack);
	}

	// Output the coset representatives
	fprintf(outfile, "#The coset representatives are\n");
	for (i = 0; i < Graph.Index; i++)
	{
		fprintf(outfile, "#");  // make it a comment
		fprintrep(outfile, &Group, &Graph, i, " ");     // Spaces for legibility
		fprintf(outfile, "\n"); // put the next one on the next line...
	}
	fprintf(outfile, "#The paths back to the identity are\n");
	for (i = 0; i < Graph.Index; i++)
	{
		fprintf(outfile, "#");  // make it a comment
		fprintpathback(outfile, &Group, &Graph, i, " ");        // Spaces for legibility
		fprintf(outfile, "\n"); // put the next one on the next line...
	}
	
	// Output the (non-trivial) subgroup generators
	fprintf(outfile, "#The subgroup generators are\n");
	for (i = 0; i < Graph.Index; i++)               // For each coset
	{
		for (j = 1; j <= Group.NumGens; j++)    // For each group generator
		{
			// The subgroup generator consists of the path to the coset,
			// the group generator, and the path back to the identity
			// from the new coset, all freely reduced.
			if ( !isSchrier( &Graph, i, j ) )
			{
				fprintf(outfile, "#S");
				fprintrep(outfile, &Group, &Graph, i, "");
				fprintf(outfile, "_%s = ", Group.GenLabel[j-1] );
				fprintrep(outfile, &Group, &Graph, i, "");
				fprintf(outfile, " %s ", Group.GenLabel[j-1] );
				fprintpathback(outfile, &Group, &Graph, Graph.Coset[i].Generator[j-1], "");
				fprintf(outfile, "\n");
			}
			// If the composition of the path to the coset with the 
			// generator _is_ the path to the new coset, then the 
			// word freely reduces, so just output 'generator' = 1
			// where 'generator' is of the form S_{'coset rep', 'gen'}
			// where 'coset rep' is the string of generator symbols
			// which is the path to the coset and 'gen' is the
			// generator symbol 
		}
	}
	
	// For each relator, expressed as a product of the (big) group generators
	//      Read and convert to integer representation and store
	//      Starting at the identity coset, follow the generators around
	//              the coset graph.
	//      If the relator doesn't end at the identity, print a warning message
	//              and quit.
	//      Otherwise, 
	//      For each coset,
	//              Rewrite the relator, conjugated by that coset representative,
	//              as a product of the subgroup generators
	fclose(groupfile);
	fclose(cosetfile);
	if (output)
		fclose(outfile);
}

void usage()
{
	fprintf(stdout,"\
Usage:\n\
schrier <coset information file> <group information file> [<output file>]\n\
\n\
The program takes a finitely presented group G = <g,...|R,...> and coset\n\
representatives for a subgroup H and gives a presentation for H.\n\
\n\
The second argument, if any, is assumed to be the group relator file.\n\
\n\
Input file structure:\n\
Group file structure:\n\
Output file:\n\
The output file is an ascii file, using Tex conventions for \n\
subscripting, that consists of the Schrier (s) coset \n\
representatives, the (s,g) subgroup generators, the (sRS)\n\
relations of the subgroup, and the (sRS) relations written\n\
in terms of the (s,g) generators.\n\
\n");

} /* end usage */

