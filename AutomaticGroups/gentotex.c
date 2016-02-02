/* File GenToTex.C
Takes lines of non-zero integers 
x1,...,xn
and outputs lines
$$[g/G]_{x1},...,[g/G]_{xn}$$
where g or G is chosen depending on whether the integer is positive or negative.*/

#include <stdlib.h>
#include <stdio.h>

void main(argc, argv)
int argc;
char *argv[];
{
	FILE *infile;	/* Input file */
	int	intin;	/* Input integer */

	if (argc > 1)
	{
		infile = fopen(argv[1],"r");
		if (infile == NULL)
		{
			fprintf(stderr, "GENTOTEX: Unable to open %s\n",
					argv[1]);
			
		} /* empty input file */
		else
		{
			while (!feof(infile) && fscanf(infile, "%d",&intin) )
			{
				if (intin > 0)
					fprintf(stdout,"g_{%d} ",intin);
				else
					if (intin < 0)
						fprintf(stdout,"G_{%d} ",intin);
					else
						fprintf(stderr,"GENTOTEX error: generator in file %s is 0.\n",argv[1]);
			}
		}
	}
	else
		usage();
}

usage()
{
	fprintf(stderr,"\
Usage\n\
	GENTOTEX <genfile>\n\
where <genfile> is a text file of lines of non-zero integers.\n\
The program takes a line such as\n\
1 3 -5 34 98 -2 -56\n\
and \
outputs the line\n\
$$g_{1} g_{3} G_{5} g_{34} g_{98} G_{2} G_{56}$$\n\
Without the -c option the output would be\n\
$$g_{1} g_{3} g_{5}^{-1} g_{34} g_{98} g_{2}^{-1} g_{56}^{-1}$$\n\
Output is to stdout and may be redirected.\n\
Errors are to stderr so shouldn't get redirected.\n");

}
/* if the option -c (for displaying inverses as Capitals) is given,\n\ */
