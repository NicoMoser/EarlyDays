
/* Program to "invert" a file of strings.  It reverses the order of the 
letters and swaps upper and lower case.  

Input is a text file of lines. For each line l and each relation in argv[3], 
argv[4], ... form the word 

l argv[k] L

where L is the inverted string l.

If no relations are given, output is just the inverted words of argv[1].
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 200

void main(argc, argv)
int argc;
char *argv[];
{

	char wordin[MAXLINE]; /* maximum letters in a word is MAXLINE */
	char wordout[MAXLINE];

	FILE *fin, *fout;

	int i,len;

	if (argc < 3) {
		printf("\n\
Usage: invert <Input file> <Output file> [R1] [R2] ...\n\n\
<Input file> is a text file where the lines are assumed to be words in some\n\
generators.\n\n\
<Output file> will look the same, except that the strings will be in reverse\n\
order and upper case will be switched with lower case.\n\n\
The parameters <R1>, <R2>, etc. are RELATIONS in the generators. For each\n\
line l in <Input file> and each relation R, the line consisting of l R L\n\
is formed and added to <Output file>.\n\n\
Bugs: If a generator is more than one character long, all the characters are\n\
reversed.\n");
		exit(0);
	}
	else

/* the file argv[1] contains lines consisting of the strings to invert */

	fin = fopen(argv[1],"r"); 
	fout = fopen(argv[2],"w");

	if (!(fin) || !(fout)) {
		exit(0);
	}
	

	while (fgets(wordin,MAXLINE, fin)) {
		/* remove \n character from wordin */
		/* assume wordin[len-1] == /n */
		len = strlen(wordin)-1;
		wordin[len] = '\0';
		/* now strlen(wordin) is one less */
		strcpy(wordout, wordin);
		for (i = 0; i < len; i++) {
			wordout[i] = (isupper(wordin[len-i-1]) ? tolower(wordin[len-i-1]) : toupper(wordin[len-i-1]));
		}
		
		printf("%s %s\n",wordin,wordout);
		
		if (argc > 3) {
			for (i=3; i < argc; i++) {
				fprintf(fout,"%s%s%s\n",wordin,argv[i],wordout);
			}
		} 
		else
			fprintf(fout,"%s\n",wordout);
		
	}

	fclose(fin);
	fclose(fout);

}
