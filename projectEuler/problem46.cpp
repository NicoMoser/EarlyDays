/*

It was proposed by Christian Goldbach that every odd composite number
can be written as the sum of a prime and twice a square.

9 = 7 + 2*1^2
15 = 7 + 2*2^2
21 = 3 + 2*3^2
25 = 7 + 2*3^2
27 = 19 + 2*2^2
33 = 31 + 2*1^2

It turns out that the conjecture was false.

What is the smallest odd composite that cannot be written as the sum
of a prime and twice a square?

for all j in 1 ... sqrt( (n-2)/2 )
n - 2*j^2 is composite

*/

#include "primes.h"
#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

bool has_goldbach_representation( int i, const bitset<sieve_size> & sieve )
{
  int count = 0;
  for ( int j = 1; i - 2*j*j > 1; ++j ) {
    int c = i - 2*j*j;
    cout << "testing " << j << endl;
    if ( !sieve[c] ) {
      cout << i << " is an odd composite with " << i << " = " << c << " + 2*" << j << "^2 where " << c << " is composite" << endl;
      count++;
    } else {
      cout << i << " = " << c << " + 2*" << j << "^2 satisfies Goldbach's proposal" << endl;
      return true;
    }
  }
  if ( count > 0 ) {
    return false;
  }
}

int main( int argc, char* argv[] )
{
  cout << "generating primes" << endl;

  bitset<sieve_size> sieve = get_sieve();

  cout << " testing" << endl;

  for (int i = 9; i < sieve_size; i+=2) {
    if ( !sieve[i] ) { // i is an odd composite
      cout << i << " is an odd composite" << endl;
      if ( has_goldbach_representation( i, sieve ) ) {
	continue;
      } else {
	cout << i << " is an odd composite that can not be written as a sum of a prime and twice a square" << endl;
	return 0;
      }
    }
  }
}
