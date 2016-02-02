/* 	Program Name : LabGroup
	Author : Leon Moser
	Date : August 20, 1993

	Program : If the text file "LABGROUP.TXT" or, optionally, a file
	specified on the command line, is present, the first 32 lines of the
	file are assumed to be the names of the students in the class. They
	are ordered by section.

	If the file has fewer than 32 lines the user is alerted and shown
	the names. The user is given the option of continuing with the file
	as shown, manually adding names, entering all the names by hand,
	or quitting. If a file is specified but not found or not specified
	and the default file isn't found, the user is prompted to type
	in 32 students' names. They are to be typed in one section at a time.

	It is assumed that the first two from the first
	section will be grouped with the first two from the second section,
	the third and fourth from the first section grouped with the third
	and fourth from the second section, and so on.

	The program reorders the names so that no two students are paired
	together twice and displays the groups of names. By pressing the
	<TAB> key, the user may cycle through six such orderings of the
	names. <Shift-Tab> cycles in reverse order. <Esc> returns to the
	original, unsorted, order.

	No two students are paired twice in the six orderings.

	The user may select two names to switch positions on the display.
	Press enter to choose a name, by index number.  When two names have
	been chosen, they are swapped.
	The swaps may be removed, using the <Ctrl-R> combination.

	If desired, the roster may be printed, with the groupings selected.
	This output is formatted differently than the screen data. To print
	press <Ctrl-O>.

*/

#include <string.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define N 32 /* Number of students */
#define M 6 /* Number of orderings of N (=32) students */
#define MAXNAME 14 /* Maximum length of a name */
#define across 4 /* Number of names that fit across the screen */

#define neutralmode -1
#define quit 0
#define cycle 1
#define revcycle 2
#define restorig 3
#define unswap 4
#define filemode 5
#define help 6
#define edit 7
#define select 9
#define print 10
#define quittomain 13

	char *names[N]; /* Initial list of names */
	int p[M][N]; /* Six arrays of permutations of the N students. */
	int perm[N]; /* permutation for display purposes */
	char filename[80];


	int curr; /* index of the current arrangement of the names */
	int mode; /* selected mode or action for the program */
	int namesentered; /* positive if names have been loaded */



int getmode(void); /* determines the mode selected by the user */
int getmode(void){

	static int c;
	int i;

	printf("(F)ile menu (S)witch pair (R)emove switches (P)rint menu (Q)uit\n\
(N)ext group  (L)ast group (O)riginal group (E)dit name (H)elp\n");
	c = getchar();
	if (getchar()); /* use up extra <enter> */
	switch (c) {
		case 'o':
		case 'O' : i = restorig; break;
		case 'e' :
		case 'E' : i = edit; break;
		case 'f':
		case 'F': i = filemode; break;
		case 's':
		case 'S' : i = select; break;
		case 'n' :
		case 'N' : i = cycle; break;
		case 'l' :
		case 'L' : i = revcycle; break;
		case 'p' :
		case 'P' : i = print; break;
		case 'r' :
		case 'R' : i = unswap; break;
		case 'q' :
		case 'Q' : i = quit; break;
		case 'h' :
		case 'H' :
		default : i = help; break;
	} /* end switch (c) */
	return(i);
}

void fprintp(FILE *stream, int i, char *s); /* prints the index i, then the name, padded to
				MAXNAME length, or truncated */
void fprintp(FILE *stream, int i, char *s) {

	int j;

	if (strlen(s) < MAXNAME) {
		fprintf(stream,"%2d %s",i+1,s);
		for (j = strlen(s); j < MAXNAME; j++)
			fprintf(stream," ");
	}
	else {
		fprintf(stream,"%2d ",i+1);
		for (j=0;j < MAXNAME ; j++)
			fprintf(stream,"%c",s[j]);
	}
}

void display(FILE *fp, int order); /* displays all the names */
void display(FILE *fp, int order){

	int k;

	fprintf(fp,"\n\n");
	fprintf(fp,"Even indices are one section, odd indices are the other.\n");
	fprintf(fp,"Reordering number %d.\n\n",order+1);
	for (k=1;k<=N/across;k++) {
		switch (k % 2) {
			case 1 : fprintp(fp, 4*k-4, names[perm[4*k-4]]);
				fprintp(fp,4*k-2, names[perm[4*k-2]]);
				fprintf(fp,"  ");
				fprintp(fp,4*k, names[perm[4*k]]);
				fprintp(fp,4*k+2, names[perm[4*k+2]]);
				fprintf(fp,"\n");
				break;
			case 0 : fprintp(fp,4*k-7, names[perm[4*k-7]]);
				fprintp(fp,4*k-5, names[perm[4*k-5]]);
				fprintf(fp,"  ");
				fprintp(fp,4*k-3, names[perm[4*k-3]]);
				fprintp(fp,4*k-1, names[perm[4*k-1]]);
				fprintf(fp,"\n\n");
				break;
		}
	}
}


void readnames(void);
void readnames(void) {

	int i,j;
	char s[80];

	printf("When entering names, alternate between sections.\n");
	for (i=0;i<N;i++) {
		printf("What is the %d-th name?\n",i+1);
		gets(s);
		for (j = 0; j < strlen(s); j++)
			if (s[j] == '\n')
				s[j] = '\x0';
		if (namesentered)
			free(names[i]);
		names[i] = (char *)malloc(1+strlen(s));
		strcpy(names[i],s);
	}
	namesentered = 1;
}


int confirm(char *s);
int confirm(char *s) {

	char s2[80];

	if (s[0] == '\x0')
		printf("Type a file name and enter or <Enter> to quit.\n");
	else
		printf("Press enter for file name %s or type a new name.\nTo quit, begin the file name with a space.\n",s);
	gets(s2);
	if ( ( (s2[0] == '\x0') && (s[0] == '\x0') ) || (s2[0] == ' ') ) {
		return(0);
	}
	else {
		if (s2[0] == '\x0') {
		}
		else {
			strcpy(s,s2);
		}
		return(1);
	}
}

void dofilemode(void);
void dofilemode(void) {

	static int c = 'a', i, j;
	static char s[80];
	static FILE *fp;

	while ( (c != 'q') && (c != 'Q') ) {
		printf("(S)ave names (L)oad names (M)anually enter names (Q)uit to main menu\n");
		c = getchar();
		if (getchar()); /* use up extra <enter> */
		switch (c) {
			case 's' :
			case 'S' :
			if ( confirm(filename) ) {
				if  ( (fp=fopen(filename,"wt")) != NULL) {
					for (i=0;i<N;i++) {
						fprintf(fp,names[i]);
						fprintf(fp,"\n");
					}
				} else {
					printf("Unable to open %s.",filename);
				}
			}
			break;

			case 'l' :
			case 'L' :
			if ( confirm(filename) ) {
				if ( (fp = fopen(filename,"rt")) != NULL) {

					for (i = 0; i < N; i++) {
						fgets(s,80,fp);
						for (j = 0; j < strlen(s); j++)
							if (s[j] == '\n')
								s[j] = '\x0';
						if (namesentered)
							free(names[i]);
						names[i] = (char *)malloc(1+strlen(s));
						strcpy(names[i],s);
					}
					namesentered = 1;
					display(stdout,curr);
				} else {
					printf("Unable to open %s.\n",filename);
					filename[0] = '\x0';
				}
			}
			break;

			case 'm' :
			case 'M' :
				readnames();
				break;

			case 'q' :
			case 'Q' : break;

			default : break;
		}
	}
	c = 'a';
}

void doprintmode(void);
void doprintmode(void) {

	static int c = 'a';
	char pfile[80];
	FILE *fp;

	pfile[0] = '\x0';

	while ( (c != 'q') && (c != 'Q') ) {
		printf("Print to (F)ile   Print to (P)rinter  (Q)uit to main menu.\n");
		c = getchar();
		if (getchar()); /* skip <enter> */
		switch (c) {
			case 'f':
			case 'F':
			if (confirm(pfile)) {
				if  ( (fp=fopen(pfile,"wt")) != NULL) {
					fprintf(fp,"\n\n");
					display(fp,curr);
					fprintf(fp,"\f");
					fclose(fp);
				} else {
					printf("Unable to open %s.",pfile);
				}
			}
			break;

			// case 'p':
			// case 'P':
			// 	fprintf(stdprn,"\n\n");
			// 	display(stdprn,curr);
			// 	fprintf(stdprn,"\f");
			break;

			default : break;
		} /* switch */
	} /* while */
	c = 'a';
}


void selectnames(void);
void selectnames(void) {

	char t[80];
	int sel, sel2, temp;

	printf("\nChoose a name by index number between 1 and %d. ",N);
	sel = 0;
	while (sel < 1 || sel > N) {
		gets(t);
		sel = atoi(t);
	}
	printf("You chose %s.",names[perm[sel-1]]);
	printf("\nChoose a second name. ");
	sel2 = 0;
	while (sel2 < 1 || sel2 > N) {
		gets(t);
		sel2 = atoi(t);
	}
	printf("You chose %s.", names[perm[sel2-1]]);
	if (sel2 - sel) {
		temp = perm[sel-1];
		perm[sel-1] = perm[sel2-1];
		perm[sel2-1] = temp;
	}
}

void editname(void);
void editname(void) {

	char t[80];
	int sel, j;

	printf("\nChoose a name by index number between 1 and %d. ",N);
	sel = 0;
	while (sel < 1 || sel > N) {
		gets(t);
		sel = atoi(t);
	}
	printf("You chose %s.\n",names[perm[sel-1]]);
	printf("Enter the new name.\n");
	gets(t);
	for (j = 0; j < strlen(t); j++)
		if (t[j] == '\n')
			t[j] = '\x0';
	free(names[perm[sel-1]]);
	names[perm[sel-1]] = (char *)malloc(1+strlen(t));
	strcpy(names[perm[sel-1]],t);
}

void printhelp(void);
void printhelp(void) {
	printf("\n\
Press <N> to see the next ordering of the names, or <L> to see the\n\
previous one. Press <O> to return to the original ordering.\n\
Press <F> to load, save, or manually enter names.\n\
Press <E> to edit a name.\n\
Press <S> to select two names by index.  Their positions will be switched.\n\
Press <R> to remove any manually selected switches.\n\
Press <P> to print out the ordering shown to a file or your printer.\n\
Press <Q> to quit.\
");

}

int main(int argc, char *argv[]);
int main(int argc, char *argv[]) {

	int i;

	printf("\nLABGROUP Version 1.0 by Leon Moser, Duke University.\n\n");

	/* initialize permutation arrays */

	for (i=0;i<N;i++)
		perm[i] = p[0][i] = i;

	p[1][0] = 0;   p[1][1] = 9;   p[1][2] = 4;   p[1][3] = 13;
	p[1][4] = 2;   p[1][5] = 11;  p[1][6] = 6;   p[1][7] = 15;
	p[1][8] = 8;   p[1][9] = 1;   p[1][10] = 12; p[1][11] = 5;
	p[1][12] = 10; p[1][13] = 3;  p[1][14] = 14; p[1][15] = 7;
	p[1][16] = 16; p[1][17] = 25; p[1][18] = 20; p[1][19] = 29;
	p[1][20] = 18; p[1][21] = 27; p[1][22] = 22; p[1][23] = 31;
	p[1][24] = 24; p[1][25] = 17; p[1][26] = 28; p[1][27] = 21;
	p[1][28] = 26; p[1][29] = 19; p[1][30] = 30; p[1][31] = 23;

	p[2][0] = 0;   p[2][1] = 17;  p[2][2] = 6;   p[2][3] = 23;
	p[2][4] = 2;   p[2][5] = 19;  p[2][6] = 4;   p[2][7] = 21;
	p[2][8] = 8;   p[2][9] = 25;  p[2][10] = 14; p[2][11] = 31;
	p[2][12] = 10; p[2][13] = 27; p[2][14] = 12; p[2][15] = 29;
	p[2][16] = 16; p[2][17] = 1;  p[2][18] = 22; p[2][19] = 7;
	p[2][20] = 18; p[2][21] = 3;  p[2][22] = 20; p[2][23] = 5;
	p[2][24] = 24; p[2][25] = 9;  p[2][26] = 30; p[2][27] = 15;
	p[2][28] = 26; p[2][29] = 15; p[2][30] = 28; p[2][31] = 13;

	p[3][0] = 0;   p[3][1] = 7;   p[3][2] = 8;   p[3][3] = 15;
	p[3][4] = 2;   p[3][5] = 5;   p[3][6] = 10;  p[3][7] = 13;
	p[3][8] = 4;   p[3][9] = 3;   p[3][10] = 12; p[3][11] = 11;
	p[3][12] = 6;  p[3][13] = 1;  p[3][14] = 14; p[3][15] = 9;
	p[3][16] = 16; p[3][17] = 13; p[3][18] = 24; p[3][19] = 31;
	p[3][20] = 18; p[3][21] = 21; p[3][22] = 26; p[3][23] = 29;
	p[3][24] = 20; p[3][25] = 19; p[3][26] = 28; p[3][27] = 27;
	p[3][28] = 22; p[3][29] = 17; p[3][30] = 30; p[3][31] = 25;

	p[4][0] = 0;   p[4][1] = 19;  p[4][2] = 10;  p[4][3] = 25;
	p[4][4] = 2;   p[4][5] = 17;  p[4][6] = 8;   p[4][7] = 27;
	p[4][8] = 4;   p[4][9] = 23;  p[4][10] = 14; p[4][11] = 29;
	p[4][12] = 6;  p[4][13] = 21; p[4][14] = 12; p[4][15] = 31;
	p[4][16] = 16; p[4][17] = 3;  p[4][18] = 26; p[4][19] = 9;
	p[4][20] = 18; p[4][21] = 1;  p[4][22] = 24; p[4][23] = 11;
	p[4][24] = 20; p[4][25] = 7;  p[4][26] = 30; p[4][27] = 13;
	p[4][28] = 22; p[4][29] = 5;  p[4][30] = 28; p[4][31] = 15;

	p[5][0] = 0;   p[5][1] = 5;   p[5][2] = 14;  p[5][3] = 11;
	p[5][4] = 2;   p[5][5] = 7;   p[5][6] = 12;  p[5][7] = 9;
	p[5][8] = 4;   p[5][9] = 1;   p[5][10] = 10; p[5][11] = 15;
	p[5][12] = 6;  p[5][13] = 3;  p[5][14] = 8;  p[5][15] = 13;
	p[5][16] = 16; p[5][17] = 21; p[5][18] = 30; p[5][19] = 27;
	p[5][20] = 18; p[5][21] = 23; p[5][22] = 28; p[5][23] = 25;
	p[5][24] = 20; p[5][25] = 17; p[5][26] = 26; p[5][27] = 31;
	p[5][28] = 22; p[5][29] = 19; p[5][30] = 24; p[5][31] = 29;

	curr = 0; /* current permutation */

	namesentered = 0;

	filename[0] = '\x0';
	if (argc > 1)
		strcpy(filename,argv[1]);

	while ( (mode = getmode()) != quit) {
		switch (mode) {
			case quit : break;

			case filemode :
			dofilemode();
			break;

			case cycle : /* Cycle Roster */
				if (namesentered) {
					curr = (++curr) % M;
					for (i=0;i<N;i++)
						perm[i] = p[curr][i];
					display(stdout,curr);
				} else
					printf("No names entered yet.\n");
				break;

			case revcycle : /* Cycle in reverse */

				if (namesentered) {
					curr = (--curr + M) % M;
					for (i=0;i<N;i++)
						perm[i] = p[curr][i];
					display(stdout,curr);
				} else
					printf("No names entered yet.\n");
				break;

			case restorig : /* Restore original */
				if (namesentered) {
					curr = 0;
					for (i=0;i<N;i++)
						perm[i] = i;
					display(stdout,curr);
				} else
					printf("No names entered yet.\n");
				break;

			case unswap : /* Restore to roster before swaps made */
				if (namesentered) {
					for (i=0;i<N;i++)
						perm[i] = p[curr][i];
					display(stdout,curr);
				} else
					printf("No names entered yet.\n");
				break;

			case select :
				if (namesentered) {
					selectnames();
					display(stdout,curr);
				} else
					printf("No names entered yet.\n");
				break;

			case print : /* PRINT */
				if (namesentered)
					doprintmode();
				else
					printf("No names entered yet.\n");
				break;

			case help :
				printhelp();
				break;

			case edit :
				if (namesentered)
					editname();
				else
					printf("No names entered yet.\n");
				break;

			default : break;
		} /* end switch */
	} /* end while */
	return 0;
} /* End Program */
