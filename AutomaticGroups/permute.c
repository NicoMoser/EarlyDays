 
#include <stdio.h>

 
typedef int perm;
typedef int gen;
typedef int *row;
typedef perm *permptr;
 
#define permlen(p) p[0]
#define wordlen(g) g[0]
 
/*                PERMUTATION FUNCTIONS                                         */
 
int permsize(p) /* Returns the word length needed to represent the
                permutation in the generators.  By Lemma 9.1.5, p. 184 of
                Epstein et al., this length is the size of the set of
                reversals of the permutation.*/
perm *p;
{
        int i,j,n=0,m;
 
        m = permlen(p); /* number of strands! */
        for (i=1; i<m; i++)
                for (j=i+1;j<=m;j++)
                        n += (p[j]<p[i]);
        return(n);
      }
 
 
 
/*                                BRAID FUNCTIONS                          */
 
/*         Function : SHOWGEN
        INPUT : The index, j, to the generator, the number of strands, n, and
                whether or not to display the inverse, inv.
        OUTPUT: (To stdout) A vertical bar followed by a space, except in
                position j and j+1, where it is space, backslash or slash,
                space, space.  If inv==0, backslash is printed.
 
 
        Example: t1t2t1 = t2t1t2
        strand generator
        1 2 3                         1 2 3
 
         \  |   t1                    |  \   t2
        |  \    t2        =            \  |  t1
         \  |   t1                    |  \   t2
 
 
*/
 
/* DISPLAY FUNCTIONS */

void showgen(j, n)
/* graphically displays the braid generator from top to bottom.
If j < 0 then show the inverse braid generator of (|j|, |j|+1). */
int j,n;
{
        int i;
 
        for (i=1;i<=n; i++)
                if (abs(j) < n)
                        fprintf(stdout,"%s",((i==abs(j)) ? ((j > 0) ? " \\" : " /") : ((i==abs(j)+1)? "  " : "| ")));
                else
                        fprintf(stdout,"%s","| ");
        fprintf(stdout,"\n");
}
 
void showbraid(g, n) /* Shows a graphical representation of
                                each of the generators in the list. */
gen *g;
int n;
{
        int i;
 
        for (i=1;i<=wordlen(g);i++)
                showgen(g[i],n);
      }
 
/*CONVERSI0N FUNCTIONS */

/* FUNCTION permtogen
	INPUT: Permutation of digits 1,...,n
	OUTPUT: List of generators which represent this permutation as a 
		non-repeating positive braid.

	METHOD: Find the smallest k_1 for which p[k_1] > p[k_1+1]. Then we must 
		switch positions of k_1 and k_1+1, so write k_1 to g[1].  Now
		remove the permutation (k_1,k_1+1) from p, calling the resulting
		permutation p_1. Starting from the beginning of p_1, find the
		smallest k_2 for which p_1[k_2] > p_1[k_2+1]. Write k_2 to g[2]
		and remove the permutation (k_2,k_2+1) from p_1, calling the
		result p_2.  Repeat this search on p_2, p_3, etc.  The process
		must end, since the maximum number of reversals of a permutation
		of n letters is n(n-1)/2.
*/ 

gen *permtogen(p) /* Lists the generators of a positive, non-repeating
                        braid which represents the permutation */

perm *p;
{
        gen *g;
        int n; /* size of list of generators */
        int i, j;
        perm temp;
 
 
        n = permsize(p); /* returns the number of reversals of p */
 
        if ((g=(gen *)malloc(sizeof(gen)*(n+1))) == NULL) 
		fprintf(stdout,"\nPERMTOGEN : Not enough memory to create array of generators.\n");
	else {
		g[0] = n; /* Store length of permutation */
			for (j=1; j<=n; j++) {
			i=1; /* Start over from the beginning of permutation */
			while (p[i]<p[i+1]) i++; /* Find first reversal of p */
			g[j] = i; /* Set j-th generator of g to reversal i */
			temp = p[i]; /* Remove this reversal from p */
			p[i] = p[i+1];
			p[i+1] = temp;
		}
 
	}
        return(g);
}
 
void cancel(g)
gen *g; 
{

        int i, j;
 
        for (i = 1; i < wordlen(g); i++) { 
		/* only need to check up to 2nd to last generator */
		if (g[i] + g[i+1] == 0) {
			for (j = i; j+1 < wordlen(g); j++) {
				g[j] = g[j+2]; /* skip g[i], g[i+1] */
			}
                        wordlen(g) -= 2; /* shorten g */
		}
	}
}

int firstnegindex(g)
gen *g;
{ /* return the index of the first negative generator 
to the left of a positive one, starting from the right. */

	int i;
 
	i = wordlen(g);
 
	/* find first positive generator from the right */
	while (g[i--] < 0); /* assumes g[0] is positive, so it will stop there */
	i++;
	/* if its index is one, or none found, want i = 0 */
	if (i < 2)
		return(0);
	else
	/* otherwise, search to the left of that point for a negative
	generator.  if none found, return 0, otherwise return index */
		while ( (g[i] > 0) && (i) )
			--i;
		return(i);
}

gen *canonform(g)
gen *g;
{
 
        /* Cancel all the pairs of generators and their negatives.
        Move all the negative generators to the end of the braid.
        Uses the relation
 
                         -1                 -1   -1
                        x   x    = x    x  x    x      (same with i-1)
                         i   i+1    i+1  i  i+1  i
                                                                        */
 
        int negindex, i;
        gen tempgen;
        gen *g2;
 
 
        while ( (negindex = firstnegindex(g)) != 0 ) { /* while there are negative generators
                        to the left of positive ones */
                /* check if g[negindex] cancels its neighbor(s) */
                /* check right first */
                if (g[negindex] + g[negindex + 1] == 0) {
                        /* cancel these two */
                        if ( (g2 = (gen*)malloc( (wordlen(g)-1)*sizeof(gen) ) ) == NULL) {
                                        printf("\ncanonical form : not enough memory.");
				      } else {
                                for (i = 0; i < negindex; i++)
                                        g2[i] = g[i];
                                for (i = negindex; i+2 <= wordlen(g); i++)
                                        g2[i] = g[i+2];
                                wordlen(g2) -= 2;
                                free(g);
                                /* copy g2 back into g */
                                if ((g = (gen *)malloc((wordlen(g2)+1)*sizeof(gen)))==NULL) {
                                        printf("\ncanonical form : not enough memory.");
				      } else {
                                        for (i=0;i<=wordlen(g2); i++)
                                                g[i] = g2[i];
                                        free(g2);
				      }
			      }
		      } else { /* if negindex > 1, check to the left */
                        if ( (negindex > 1) && (g[negindex] + g[negindex-1] == 0) ) {
                                /* cancel these two */
                                if ( (g2 = (gen*)malloc( (wordlen(g)-1)*sizeof(gen) ) ) == NULL) {
                                        printf("\ncanonical form : not enough memory.");
				      } else {
                                        for (i = 0; i < negindex; i++)
                                                g2[i] = g[i]; /* copy up to negindex */
                                        for (i = negindex; i+2 <= wordlen(g); i++)
                                                g2[i] = g[i + 2]; /* copy after negindex+1 */
                                        wordlen(g) -= 2;
                                        free(g);
                                        /* copy g2 back into g */
                                        if ((g = (gen *)malloc((wordlen(g2)+1)*sizeof(gen)))==NULL) {
                                                printf("\ncanonical form : not enough memory.");
					      } else {
                                                for (i=0;i<=wordlen(g2); i++)
                                                        g[i] = g2[i];
                                                free(g2);
					      }
				      }
			      } /* end if : nothing cancelled */
                        /* check if it commutes to the right */
                        if ( abs( g[negindex+1] + g[negindex] ) - 1 ) {
                                /* swap */
                                tempgen = g[negindex];
                                g[negindex] = g[negindex+1];
                                g[negindex+1] = tempgen;
			      } else { /* replace by relation */
                                if ( (g2 = (gen*)malloc( (wordlen(g)+3)*sizeof(gen) ) ) == NULL) {
                                        printf("\ncanonical form : not enough memory.");
				      } else {
                                        for (i = 1; i < negindex; i++)
                                                g2[i] = g[i];
                                        g2[negindex] = g[negindex+1];
                                        g2[negindex+1] = -g[negindex];
                                        g2[negindex+2] = -g[negindex+1];
                                        g2[negindex+3] = g[negindex];
                                        for (i = negindex + 2; i <= wordlen(g); i++)
                                                g2[i+2] = g[i];
                                        wordlen(g2) = wordlen(g) + 2;
                                        free(g);
                                        /* copy g2 back to g */
                                        if ( (g = (gen*)malloc( (wordlen(g2)+3)*sizeof(gen) ) ) == NULL) {
                                                printf("\ncanonical form : not enough memory.");
					      } else {
                                                for (i = 0; i <= wordlen(g2); i++)
                                                        g[i] = g2[i];
                                                free(g2);
					      }
				      }
			      }
		      }
	      }
        return(g);
      }
 





 
/*        PERMUTATION FUNCTIONS                                        */
 
 
/*
        Function : NOT
        INPUT : an array a[0..n], where a[0]=n, and the other elements are
                a permutation of the numbers 1,...,n.
        OUTPUT : an array of the same format, representing left
                multiplication of the input permutation by the permutation
                omega, which sends (1,...,n-1) to (n-1, n-2,...,1).
 
        Example:
 
        not(6 2 4 1 3 5)
 
        will compute the permutation which is the product of 6 5 4 3 2 1
        and 6 2 4 1 3 5.
*/
 
 
/*
        Function : MIN
        INPUT : two arrays of the form a[0..n], where a[0]=n, and the other
                elements are a permutation of the numbers 1,...,n.
        OUTPUT : an array of the same form representing the permutation
                which is the greatest lower bound of the two permutations
                input.  The ordering is given by s < t if Rs < Rt, where
                Rs = {(i,j) : 1<=i<j<=n and s(j) < s(i) }.  See section 9.1 of
                Word Processing in Groups, by Epstein et al.
 
 
        Example :
        min(6 2 4 1 3 5, 1 4 6 3 5 2)
 
        will compute the permutation which is the greatest lower bound
        for the two permutations shown.
*/
 
 
/*
        Function : MAX
        INPUT : two arrays of the form a[0..n], where a[0]=n, and the other
                elements are a permutation of the numbers 1,...,n.
        OUTPUT : an array of the same form, representing the permutation
                which is the least upper bound of the two permutations
                input.  It is defined to be not(min(not(a),not(b))).
                The ordering is given by s < t if Rs < Rt, where
                Rs = {(i,j) : 1<=i<j<=n and s(j) < s(i) }.  See section 9.1 of
                Word Processing in Groups, by Epstein et al.
 
 
        Example:
        max(6 2 4 1 3 5, 1 4 6 3 5 2)
 
        will compute the permutation which is the least upper bound
        for the two permutations shown.
*/
 
 
void printp(p) /* prints the entries of p to stdout */
perm *p;
{
        int i, n;
        n = permlen(p);
        for (i=1; i < n; i++)
                fprintf(stdout,"%d%c",p[i],',');
        fprintf(stdout,"%d",p[n]);
      }
 
perm *strtoperm(s) /* this routine converts a string of the
                        form x1,x2,...,xn to an array of the integers
                        n,x1,...,xn */
char *s;
{
        int i, n;
        perm *p=NULL;
 
        i=0;
        n=1;
        while (i<strlen(s)) {
                if (s[i++] == ',') n++;
	}
        if ( (p = (perm *)malloc(sizeof(perm)*(n+1)) ) == NULL )  {
                fprintf(stdout,"\nMemory not found.");
	} else {
                /* Load the permutation array with the numbers from s */
		for (i = 1; i < n; i++) {
			p[i] = atoi(s);
			while (s[0] != ',') ++s;
                        ++s;
		}
		p[i] = atoi(s);
        p[0] = n;
	}
	return(p);
}
 
gen *strtogen(s) /* this routine converts a string of the
                        form x1,x2,...,xn to an array of the integers
                        n,x1,...,xn, representing the braid generators */
char *s;
{
        int i, n;
        gen *g=NULL;
 
        i=0;
        n=1;
        while (i<strlen(s)) {
                if (s[i++] == ',') n++;
	      }
        if ( (g = (gen *)malloc(sizeof(gen)*(n+1)) ) == NULL )  {
                fprintf(stdout,"\nMemory not found.");
	      } else {
                /* Load the braid array with the numbers from s */
                for (i = 1; i < n; i++) {
                        g[i] = atoi(s);
                        while (s[0] != ',') ++s;
                        ++s;
		}
		g[n] = atoi(s);
                g[0] = n;
	}
        return(g);
}
 
 
perm *inv(p)
perm *p;
{
        int n, i;
        perm *p2;
 
        i = 1;
        n = permlen(p);
 
        if ((p2=(perm *)malloc(sizeof(perm)*(n+1)))==NULL) fprintf(stdout,"\nNOT: Not enough memory to invert permutation.");
        p2[0] = n;
        for (i=1; i <= n; i++)
                p2[i] = n + 1 - p[i];
        return(p2);
}

perm *inf(p1, p2)
perm *p1, *p2;
{
        row *r;         /* r is the set of reversals of the minimum. */
        int i, j, k, n, mem;
        perm *p=NULL;
 
/*
  { Should verify that the two arguments are valid permutations.
        Assume for now that whatever passed the arguments gave valid
        arguments. }
*/
        n = permlen(p1); /* Assume the same length. */
        if ((p=(perm *)malloc(sizeof(perm)*(n+1))) == NULL) 
		fprintf(stdout,"\nMIN : Not enough memory to create new permutation.");
        else {
                mem = 0;
                if ( (r = (row *)malloc(sizeof(row)*(n-1)) ) == NULL) 
			fprintf(stdout,"\nMIN: Not enough memory to create array of pointers to reversal array.");
                else {
			for (i=0;i<n-1;i++)
                        	mem += ((r[i] = (int *)malloc(sizeof(row)*(n-i-1))) == NULL);
                        if (mem) 
				fprintf(stdout,"\nMIN: Not enough memory to create reversal array.");
                        else {
                                for (i=1;i<n;i++) {
                                        /* Initialize */
                                        for (j=i+1; j<=n; j++) {
                                                r[i-1][j-i-1] = (p1[j]<p1[i])&&(p2[j]<p2[i]);
					      }
				      }
                                for (i=1; i<n; i++) {
                                        for (j=i+2; j<=n; j++) {
                                                if (r[i-1][j-i-1]) {
                                                        k=i+1;
                                                        while (k<j) {
                                                                r[i-1][j-i-1] *= r[i-1][k-i-1]+r[k-1][j-k-1];
                                                                k++;
							      }
						      }
					      }
				      }
                                /* Determine the permutation given by the list of reversals, r.*/
                                p[0] = n;
                                for (i=1;i<=n;i++) {
                                        p[i]=1;
                                        for (j=1; j<i; j++)
                                                p[i] += (r[j-1][i-j-1]==0);
                                        for (j=i+1; j<=n; j++)
                                                p[i] += (r[i-1][j-i-1] != 0);
				      }
                                for (i=n-2;i==0;i--)
                                        free(r[i]);
                                free(r);
				}
			}
		}
        return(p);
}
 
perm *sup(p1, p2)
perm *p1, *p2;
{
        perm *p=NULL;
 
        if ((p=(perm *)malloc(sizeof(perm)*(permlen(p1)+1))) == NULL)
		fprintf(stdout,"\nSUP : Not enough memory to create permutation.");
        else {
                p = inv(inf(inv(p1),inv(p2)));
	}
        return(p);
}
 
perm *prod(p1, p2) 
/* implements left multiplication of p2 by p1 */
perm *p1, *p2;
{
        perm *p=NULL;
        int i;
 
        if ((p=(perm *)malloc(sizeof(perm)*(p1[0]+1))) == NULL)
                fprintf(stdout,"\nPROD: Not enough memory to create permutation.");
        else {
                p[0] = p1[0];
                for (i=1; i<=p1[0]; i++)
                        p[i] = p1[p2[i]];
	}
        return(p);
}
 
perm *permgenerator(i, n) /* Returns permutation (1 2 ... i-1 i+1 i i+2 ...n) */
                        /* If i<1 or i>=n, returns (1 2 3 4...n) (identity) */
int i,n;
{
        perm *p=NULL;
 
        if ((p=(perm *)malloc(sizeof(perm)*(n+1))) == NULL)
                fprintf(stdout,"\nGEN: Not enough memory to create permutation.");
        else {
                p[0] = n;
                for (i=1; i<=n; i++)
                        p[i]=i;
                if ((i>=1)&&(i<n)) {
                        p[i] = i+1;
                        p[i+1] = i;
		}
	}
        return(p);
}
 
int numstrands(g) 
gen *g;
{
        /* Returns 1 plus the largest absolute value in g */
        int n, i;
 
        n = 0;
        for (i = 1; i <= wordlen(g); i++) {
		n = (n > abs(g[i]) ? n : abs(g[i]));
	}
	return(++n);
}
 

int lessorequal(p1, p2)
 
/* Returns 1 if the set of reversals of p1 is contained in the set
of reversals of p2; -1 if the other way around, but not equal; 0 if
neither is contained in the other, or if permlen(p1) != permlen(p2). */
perm *p1, *p2; 
{
        int i,j,
        p1inp2 = 1, p2inp1 = 1;
 
 
        if (permlen(p1) != permlen(p2))
                return(0);
        else
                for (i = 1; i < permlen(p1); i++)
                        for (j = i + 1; j <= permlen(p1); j++) {
                                p1inp2 = p1inp2 && !((p1[j] < p1[i]) && (p2[j] > p2[i]));
                                p2inp1 = p2inp1 && !((p2[j] < p2[i]) && (p1[j] > p1[i]));
			      }
                if (p1inp2) return(1);
                if (p2inp1) return(-1);
                return(0);
      }
 
void main(argc, argv)
int argc;
char *argv[];
{
        int n;
 
        if (argc <= 1) {
                fprintf(stdout,"\n\
USAGE: permute [-b[<m>]] x1,...,xn [y1,...,yn]\n\n\
Here x1,...,xn determines a permutation of 1,...,n, and y1,...,yn determines another permutation of 1,...,n.\n\
x1,...,xn may be braid generators if -b<m> is used.\n\
Use negative numbers to represent inverse generators.  The optional positive integer <m> is the total number of strands.  If less than the absolute value of a generator, that generator will not be displayed.  If m is not given, the fewest number of strands will be used.\n\n\
If two arguments are passed, the -b option will be ignored and the output will include the infimum and supremum of the two arguments.  Also, a non-repeating positive braid representing each permutation will be displayed followed by a braid for the inf and sup.  If the two permutations lie on the same geodesic to the element omega = (n,n-1,...,2,1) in the Cayley graph, one will be shorter than the other and this order will be indicated.  If not, they are said to be not directly comparable.\n\n\
If only a single permutation is passed, the non-repeating positive braid representing this permutation will be displayed.\n\n\
DISCLAIMER: Not responsible for results if a non-permutation is a parameter but the -b option is not invoked.\n\n\
PERMUTE : A program by Leon Moser, Duke University.\n\
e-mail : moser@math.duke.edu\n\
September 8, 1993\n\
");
	      } else
                if (argc <= 2) {
			showbraid(permtogen(strtoperm(argv[1])),permlen(strtoperm(argv[1])));
		      } else {
                        /* Look for '-' and 'b' in first argument */
                        if ( (argv[1][0] == '-') && (argv[1][1] == 'b')) {
                                ++argv[1];
                                ++argv[1];
                                fprintf(stdout,"\n");
                                n = atoi(argv[1]);
                                if (!n)
                                        n = numstrands(strtogen(argv[2]));
                                fprintf(stdout, "\nHere are the braid generators %s \n",argv[2]);
				showbraid( strtogen(argv[2]), n );
				fprintf(stdout,"\nHere is the same braid with all the negative generators at the end.\n");
				showbraid( canonform(strtogen(argv[2])), n );
			      } else {
                                fprintf(stdout,"\nThe permutations are : %s and %s.", argv[1], argv[2]);
                                n = lessorequal(strtoperm(argv[1]),strtoperm(argv[2]));
                                fprintf(stdout,"\n%s is %s %s",argv[1],(n == 1 ? "less than or equal to" : (n == -1 ? "greater than" : "not directly comparable to")),argv[2]);
                                fprintf(stdout,"\nTheir infimum is : ");
                                printp( inf( strtoperm(argv[1]), strtoperm(argv[2]) ) );
                                fprintf(stdout,"\nThe inverse of %s is ",argv[1]);
                                printp( inv (strtoperm(argv[1])));
                                fprintf(stdout,"\nThe inverse of %s is ",argv[2]);
                                printp( inv (strtoperm(argv[2])));
                                fprintf(stdout,"\nThe supremum of %s and %s is ",argv[1], argv[2]);
                                printp( sup( strtoperm(argv[1]), strtoperm(argv[2]) ) );
                                fprintf(stdout,"\n");
 
                                fprintf(stdout,"\n\n\n");
                                fprintf(stdout,"%s\n\n",argv[1]);
                                showbraid(permtogen(strtoperm(argv[1])),permlen(strtoperm(argv[1])));
 
                                fprintf(stdout,"\n\n\n");
                                fprintf(stdout,"%s\n\n",argv[2]);
                                showbraid(permtogen(strtoperm(argv[2])),permlen(strtoperm(argv[2])));
 
                                fprintf(stdout,"\n\n\n");
                                fprintf(stdout,"Infimum : ");
                                printp( inf( strtoperm(argv[1]), strtoperm(argv[2]) ) );
                                fprintf(stdout,"\n\n");
                                showbraid(permtogen(inf( strtoperm(argv[1]), strtoperm(argv[2]) )),permlen(inf( strtoperm(argv[1]), strtoperm(argv[2]))));
 
                                fprintf(stdout,"\n\n\n");
                                fprintf(stdout,"Supremum : ");
                                printp( sup( strtoperm(argv[1]), strtoperm(argv[2]) ) );
                                fprintf(stdout,"\n\n");
                                showbraid(permtogen(sup( strtoperm(argv[1]), strtoperm(argv[2]) )),permlen(sup( strtoperm(argv[1]), strtoperm(argv[2]))));
				}
		}
}
 
/*
        Things to add:
                Implement the finite state automaton M having state set
                the non-repeating positive braids.
                One possibility: When it enters a state, draw that state.
                See section 9.2 of "Word Processing in Groups"
 
                Find the maximal tail of a positive braid.
 
                Given some braid, put it into left or right greedy form,
                and indicate the form when displaying it.
 
                Implement the automaton W of thm. 9.2.4 (Canonical Forms are
                Regular), which recognizes left-greedy canonical form.
 
                Implement the automaton implicit in thm. 9.3.1 over the
                language of words in right-greedy canonical form.
 
                Given a string of braid generators and inverses, put it in
                right-greedy canonical form.

		Given a positive braid, put it into a canonical form of maximal
		non-repeating positive sub-braids.  (Determine such a canonical
		form!)

		OpenWindows graphical user interface!! 
*/
