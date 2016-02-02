/*

A unit fraction contains 1 in the numerator. The decimal
representation of the unit fractions with denominators 2 to 10 are
given:

    1/2	= 	0.5
    1/3	= 	0.(3)
    1/4	= 	0.25
    1/5	= 	0.2
    1/6	= 	0.1(6)
    1/7	= 	0.(142857)
    1/8	= 	0.125
    1/9	= 	0.(1)
    1/10	= 	0.1

Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It
can be seen that 1/7 has a 6-digit recurring cycle.

Find the value of d < 1000 for which 1/d contains the longest
recurring cycle in its decimal fraction part.

****

implement division into 1 - find remainders
-> use ldiv()
lldiv_t div(int numerator, int denominator);
lldiv_t ans;   // lldiv_t is a struct type containing two ints:
             // 'quot' stores quotient; 'rem' stores remainder

identify when sequence repeats (or ends)

*/

#include <iostream>
#include <set>
#include <stdlib.h>
using namespace std;


int main( int argc, char * argv[] )
{
  int max_repeating_length = 0;
  int d = 1;
  for (long long i = 2; i < 1000; i++ ) {
    // set up the numerator - first power of 10 larger than the denominator, i.
    // otherwise the quotient would be 0 and the remainder would be the denominator.
    long long num = 10;
    while ( i > num ) {
      num *= 10;
    }

    // a cycle occurs when the remainder is the same as an earlier numerator
    // but it might not start immediately (e.g. 1/6 = 0.1(6)
    int initial_numerator = num;
    int repeating_length = 0;
    set<int> numerators;
    // set this to true when we detect a cycle, then start counting
    bool counting_cycle = false;

    do {
      lldiv_t result = __gnu_cxx::lldiv(num, i);
      // cout << num << "/" << i << " has quotient=" << result.quot << " and remainder=" << result.rem << endl;
      num = result.rem;
      if ( num == 0 ) {
	// terminating decimal
	break;
      }
      while ( i > num ) {
	// cout << "i=" << i << " num=" << num << endl;
	num *= 10;
      }
      if ( counting_cycle ) {
	repeating_length++;
      }
      if ( numerators.find(num) != numerators.end() ) {
	if ( counting_cycle ) {
	  // we completed the second cycle
	  break;
	}
	// do it over again, this time counting.
	// cout << "found a cycle of numerators" << endl;
	counting_cycle = true;
	numerators.clear();
	numerators.insert(num);
      }
      numerators.insert(num);
    } while ( true );
    cout << 1 << "/" << i << " has " << repeating_length << " repeating digits" << endl << endl;
    if ( repeating_length > max_repeating_length ) {
      d = i;
      max_repeating_length = repeating_length;
    }
  }
  cout << "1/" << d << " has " << max_repeating_length << " repeating digits" << endl;
}
