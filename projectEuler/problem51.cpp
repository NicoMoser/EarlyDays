/*
By replacing the 1st digit of *3, it turns out that six of the nine
possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this
5-digit number is the first example having seven primes among the ten
generated numbers, yielding the family: 56003, 56113, 56333, 56443,
56663, 56773, and 56993. Consequently 56003, being the first member of
this family, is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not
necessarily adjacent digits) with the same digit, is part of an eight
prime value family.

find 8 primes that have the same number of digits and share 1 or more
common digits in the same position.

generate primes:
there will be up to 10 possible primes (because there are 10
replacement digits).

1 replacement digit x
2 digits total
1x, 2x, ..., 9x
x1, x2, ..., x9

for (x=0;x<10;x++) { for (i=0;i<10;i++) {
   sprintf( buf, "%d%d", i, x );
   p = atoi(buf);
   test(p);
   sprintf( buf, "%d%d", x, i );
   p = atoi(buf);
   test(p);
} }

3 digits total:
00x, 01x, ..., 99x
0x0, 0x1, ..., 9x9
x00, x01, ..., x99
(3000 total)

for (x=0;x<10;x++) { for (i0=0;i0<10;i0++) { for (i1=0;i1<10;i1++) {
   sprintf( buf, "%d%d%d", i0, i1, x );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d", i0, x, i1 );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d", x, i0, i1 );
   p = atoi(buf);
   test(p);
} } }


2 replacement digits x,x
3 digits total
0xx, 1xx, ..., 9xx
x0x, x1x, ..., x9x
xx0, xx1, ..., xx9
(300 total - 10 for each claimed digit times 10 for the (identical) wildcard,
times 3 for the positions of the combination)

for (x=0;x<10;x++) { for (i0=0;i0<10;i0++) { 
   sprintf( buf, "%d%d%d", i0, x, x );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d", x, i0, x );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d", x, x, i0 );
   p = atoi(buf);
   test(p);
} } }


4 digits total
00xx, 01xx, ..., 99xx
0x0x, 0x1x, ..., 9x9x
0xx0, 0xx1, ..., 9xx9
x0x0, x0x1, ..., x9x9
xx00, xx01, ..., xx99
(5000 total)

for (x=0;x<10;x++) { for (i0=0;i0<10;i0++) { for (i1=0;i1<10;i1++) {
   sprintf( buf, "%d%d%d%d", i0, i1, x, x );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d%d", i0, x, i1, x );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d%d", i0, x, x, i1 );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d%d", i0, x, x, i1 );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d%d", x, i0, x, i1 );
   p = atoi(buf);
   test(p);

   sprintf( buf, "%d%d%d%d", x, x, i0, i1 );
   p = atoi(buf);
   test(p);
} } }

for each open slot
    loop 0 to 9 in the slot
        loop 0 to 9 in all of the wildcard slots
            if result is prime, record the value and increment the counter
	    if the counter == 8, print the value and exit

try 6 digits with 3 wildcards
6 digits total
000xxx, 001xxx, ..., 999xxx
00x0xx, 00x1xx, ..., 99x9xx
00xx0x, 00xx1x, ..., 99xx9x
0x0xx0, 0x0xx1, ..., 9x9xx9
0x0x0x, 0x0x1x, ..., 9xx9x9
0x0xx0, 0x0xx1, ..., 9x9xx9

for (i0=0;i0<10;i0++) { for (i1=0;i1<10;i1++) { for (i2=0;i2<10;i2++) {

   what are the binary representations with 6 digits (including leading zeros)
   and exactly 3 1's.

sprintf( buf, "%d%d%d%%d%%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%d%%d%d%%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%d%%d%%d%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%d%%d%%d%%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%%d%d%d%%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%%d%d%%d%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%%d%d%%d%%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%%d%%d%d%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%%d%%d%d%%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%d%%d%%d%%d%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%d%d%d%%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%d%d%%d%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%d%d%%d%%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%d%%d%d%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%d%%d%d%%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%d%%d%%d%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%%d%d%d%d%%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%%d%d%d%%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%%d%d%%d%d%d", i0, i1, i2 );
   test(buf, 3);
sprintf( buf, "%%d%%d%%d%d%d%d", i0, i1, i2 );
   test(buf, 3);


   sprintf( buf, "%d%d%d%%d%%d%%d", i0, i1, i2 );
   // for each template, test with the 3 wildcard digits replaced by 0..9
   test(buf, 3);

   sprintf( buf, "%d%d%%d%d%%d%%d", i0, i1, i2 );
   test(buf, 3);

   sprintf( buf, "%d%d%d%d%d%d", i0, i1, i2 );
   test(buf, 3);

   sprintf( buf, "%d%d%d%d%d%d", i0, i1, i2 );
   test(buf, 3);

   sprintf( buf, "%d%d%d%d%d%d", i0, i1, i2 );
   test(buf, 3);

   sprintf( buf, "%d%d%d%d%d%d", i0, i1, i2 );
   test(buf, 3);
} } }
*/

#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include "primes.h"

using namespace std;

/*
  This is a routine that is given the number of wildcard digits (each
  of which independently varies over 0-9, inclusive), the number of
  identical digits (described as x in the comments above). It
  generates all the possible numbers with those identical digits in
  the same places.
*/
void generate_primes(int wildcards, int claimed)
{
  /*
   */
  for (int i=0;i<wildcards;i++) {
    /*
      add another wildcard digit to the output
      but how to deal with the order of the digits

      the idea is to create all the possible replacement
      strings and printf() combinations for i wildcard digits
      and claimed other digits
     */
  }
}

/*
  how to do it for one claimed digit and one wildcard?
  need to both generate the format string and sprintf() into it

  // produce 0,..., 9
  format="%d";
  for (int i=0;i<10;i++) {
    sprintf(buf,format, i);
  }

  // produce 00, 01, ..., 09, 11

  for (int j=0;j<wildcards;j++) {
      sprintf(buf,"%s%d", buf, x);
  }
 */

int test3(const char s[], const bitset<sieve_size>& primes)
{
  char buf[20] = {0};
  int primecount = 0;
  int smallest_prime = 0;
  for (int i=0;i<10;i++) {
    sprintf(buf, s, i, i, i);
    long x = atol(buf);
    if (primes[x]) {
      if ( primecount == 0 ) {
	smallest_prime = x;
      }
      primecount++;
    }
  }
  // cout << s << " generates " << primecount << " primes. The smallest is " << smallest_prime << endl;
  if (primecount == 8) {
    return smallest_prime;
  }
  return 0;
}

void display( char s[], int n )
{
  cout << s << " generates 8 primes. The smallest is " << n << endl;
}

void test_len_6_wildcard_3(const bitset<sieve_size>& primes)
{
  char buf[20];
for (int i0=0;i0<10;i0++) { for (int i1=0;i1<10;i1++) { for (int i2=0;i2<10;i2++) {
      int x;
      sprintf( buf, "%d%d%d%%d%%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%d%%d%d%%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%d%%d%%d%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%d%%d%%d%%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%%d%d%d%%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%%d%d%%d%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%%d%d%%d%%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%%d%%d%d%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%%d%%d%d%%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%d%%d%%d%%d%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%d%d%d%%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%d%d%%d%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%d%d%%d%%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%d%%d%d%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%d%%d%d%%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%d%%d%%d%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%%d%d%d%d%%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%%d%d%d%%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%%d%d%%d%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
      sprintf( buf, "%%d%%d%%d%d%d%d", i0, i1, i2 );
      if (x=test3(buf, primes)) { display(buf,x); }
    } } }
}

int main(int argc, char* argv[])
{
  // todo: reject cases with leading zeros

  const bitset<sieve_size>& sieve = get_sieve();

  // test3("%d%d%d109",sieve);
  test_len_6_wildcard_3(sieve);
  return 0;
}
