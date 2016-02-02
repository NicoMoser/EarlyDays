#include <stdio.h>

#define FAULT -1 /* When an arc isn't found in an arc-system */ 
#define numarcs 9 /* These are the actual arcs of the arc-system */
#define numspokes 18 /* These are their incoming and outgoing portions */
typedef int arc; /* An arc is an incoming or outgoing part of an edge. */

/* Input initial ordering and list of edges to switch /*

/* Output final order */

/* Switch routine:  To switch an edge X, find its wings Y1,Y2 and Y3,Y4.  Replace -Y4,-Y1 by -Y4,-X,-Y1 and replace -Y2,-Y3 by -Y2,X,-Y3.
*/


void showarc(a)
arc *a;
{
	int i;

	for (i = 0; i+1 < numspokes; i++) {
		fprintf(stdout,"%d, ",a[i]);
	}
	fprintf(stdout,"%d",a[numspokes-1]);
}

arc *strtoarc(s) /* this routine converts a string of the
                        form x1,x2,...,x18 to an array of the integers
                        x1,...,x18 */
char *s;
{
	int i;
	arc *a=NULL;
 

	if ( (a = (arc *)malloc(sizeof(arc)*numspokes) ) == NULL )  {
		fprintf(stdout,"\nMemory not found.");
	} else {
	/* Load the arc array with the numbers from s */
		for (i = 0; i+1 < numspokes; i++) {
			a[i] = atoi(s);
			while (s[0] != ',') ++s; /* go past current number */
			++s; /* go past comma */
		}
		a[i] = atoi(s);
	}
	return(a);
}

/* Routine to verify legitimate ordering:
For each edge X, find its wings : ...,Y1,X,Y2,... and ...,Y3,X,Y4,... .
Verify that ...,-Y4,-Y1,... and ...,-Y2,-Y3,... exist.
*/

int position(a,j) /* returns the position of j in the array a */
arc *a;
arc j;
{
	int i=0;


	while ( (a[i] != j) && (i < numspokes) ) 
		++i;

	if (a[i] == j) {
		return(i);
	}
	else
		return(FAULT);
}

int verify(a)
arc *a;
{
	int i,j1,j2,j3,j4,p1,p2,k1,k2,k3,k4;

	for (i = 1; i <= numarcs; i++) {
		/* find y1,i,y2 and y3,-i,y4 */
		p1 = position(a,i);
		if (p1 == FAULT) {
			fprintf(stdout,"\nverify: %d not in ",i);
			showarc(a);
			fprintf(stdout,"\n");
			return 0;
		}
		p2 = position(a,-i);
		if (p2 == FAULT) {
			fprintf(stdout,"\nverify: %d not in ",i);
			showarc(a);
			fprintf(stdout,"\n");
			return 0;
		}
		j1 = p1 - 1; /* a[j1] is y1 */
		if (j1 < 0) 
			j1 += numspokes;
		j2 = p1 + 1; /* a[j2] is y2 */
		if (j2 >= numspokes)
			j2 -= numspokes;
		j3 = p2 - 1; /* a[j3] is y3 */
		if (j3 < 0)
			j3 += numspokes;
		j4 = p2 + 1; /* a[j4] is y4 */
		if (j4 >= numspokes)
			j4 -= numspokes;

		/* confirm that -y4,-y1 and -y2,-y3 are in the list */
		k1 = position(a,-a[j4]);
		k2 = position(a,-a[j1]);
		k3 = position(a,-a[j2]);
		k4 = position(a,-a[j3]);
		if ( !( ( ((k1+1) == numspokes) && (k2 == 0) ) || ( k2 == (k1 + 1) ) ) || !( ( ((k3+1) == numspokes) && (k4 == 0) ) || ( k4 == (k3 + 1) ) ) ) {
			fprintf(stdout,"\nWings of %d are ...,%d,%d,%d,... and ...,%d,%d,%d,...\n",i,a[j1],i,a[j2],a[j3],-i,a[j4]);
			fprintf(stdout,"\nAlternate positions are %d, %d, %d, %d\n",k1,k2,k3,k4);
			return(0);
		}
	}
	return(1);
}

void insert(a,i1,i2) /* Removes arc i1 and places it one past i2 */
arc *a;
arc i1, i2;
{
	int temp,i,p1,p2;

	p1 = position(a,i1);
	p2 = position(a,i2);
	if (p1 < p2) {
		temp = a[p1];
		for (i = p1; i<p2; i++)
			a[i] = a[i+1];
		a[p2] = temp;
	} else {
		temp = a[p1];
		for (i = p1; i>p2; i--)
			a[i] = a[i-1];
		a[p2+1] = temp;
	}
}

void swap(a,i)
arc *a;
int i;
{
	int 	p1, p2, 
		j1, j2, 
		k1, k2;


	p1 = position(a,i);
	p2 = position(a,-i);

	if ( (p1 == FAULT) || (p2 == FAULT) ) 
		return;
	else {
		j1 = p2 + 1; /* a[j1] is y4 */
		if (j1 >= numspokes)
			j1 -= numspokes;
		j2 = p1 + 1; /* a[j2] is y2 */
		if (j2 >= numspokes)
			j2 -= numspokes;

		k1 = -a[j1];
		k2 = -a[j2];

		insert(a,i,k1);
		insert(a,-i,k2);
	}
}

void main(argc, argv)
int argc;
char *argv[];
{

/* argv[1] should consist of the initial order a1,a2,...,a18, where each a_i is between -9 and 9 and non-zero.  Each such number should appear exactly once.  Also, the order should satisfy the property given in the Routine to verify legitimate ordering.  argv[2],...,argv[argc-1] should be integers from 1 to 9.
*/
	int i;
	arc *a = NULL;
	
	if (argc > 1) {
		a = strtoarc(argv[1]);
		if (verify(a)) {
			for (i = 2; i < argc; i++) {
				swap(a,atoi(argv[i]));
			}
			showarc(a);
			fprintf(stdout,"\n");
		} else {
			fprintf(stdout,"\nInvalid arcsystem: %s\n",argv[1]);
		}
	} else {
		fprintf(stdout,"\n\
USAGE: arcsys a1,...,a18 [b1][b2]...[bk]\n\n\
Each a_i is a unique non-zero integer between -9 and 9.\n\
The a_i's must satisfy the following property.  If a1,...,a18 contains ...,Y1,X,Y2,... and ...,Y3,-X,Y4,..., then it must also contain ...,-Y4,-Y1,... and ...,-Y2,-Y3,... .  (Notice that the list is treated as a cyclic one, so that a1 follows a18.)\n\n\
The optional parameters b1 through bk must be integers between 1 and 9, inclusive.  For each one read, the list a1,...,a18 will be modified as follows.  If the list contains ...,Y1,X,Y2,... and ...,Y3,-X,Y4,..., then ...,-Y4,-Y1,... and ...,-Y2,-Y3,... will be replaced by ...,-Y4,X,-Y1,... and ...,-Y2,-X,-Y3,..., respectively.  The output is the final order of a1,...,a18 after making such switches.\n\n\
ARCSYS : A program by Leon Moser, Duke University.\n\
e-mail : moser@math.duke.edu\n\
Copyright September 26, 1993\n\n");
	}
}
