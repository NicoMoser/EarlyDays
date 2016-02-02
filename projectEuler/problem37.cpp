/*

The number 3797 has an interesting property. Being prime itself, it is
possible to continuously remove digits from left to right, and remain
prime at each stage: 3797, 797, 97, and 7. Similarly we can work from
right to left: 3797, 379, 37, and 3.

Find the sum of the only eleven primes that are both truncatable from
left to right and right to left.

NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

*/

#include "primes.h"
#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <stdlib.h>

using namespace std;

bool is_truncatable_prime( int p, const bitset<sieve_size> &sieve )
{
  cout << "testing prime " << p << endl;
  if ( p < 10 ) {
    cout << "skipping one-digit primes" << endl << endl;
    return false;
  }

  int q = p;
  int power = 1;

  // truncate from the right
  q /= 10;
  while ( q > 0 ) {
    cout << "testing truncated prime " << q << endl;    
    if ( !sieve[q] ) {
      cout << q << " is not prime" << endl << endl;
      return false;
    }
    q /= 10;
    power *= 10;
  }

  cout << p << " is less than " << power*10 << endl;

  // now we know the power of 10 to start modding
  // to truncate from the left
  q = p;
  while ( power > 1 ) {
    q = q % power;
    cout << "testing truncated prime " << q << endl;    
    if ( !sieve[q] ) {
      cout << q << " is not prime" << endl << endl;
      return false;
    }
    power /= 10;
  }
  cout << "all truncated versions of " << p << " are prime" << endl << endl;
  return true;
}

int main(int argc, char* argv[])
{
  int limit = sieve_size;
  if ( argc > 1 ) {
    limit = atoi( argv[1] );
  }
  const vector<int> &primes = get_primes();
  const bitset<sieve_size> &sieve  = get_sieve();
  cout << "there are " << primes.size() << " primes " << endl;
  int count = 0;
  int sum = 0;
  for ( vector<int>::const_iterator p = primes.begin(); p != primes.end() && *p < limit; ++p) {
    if ( is_truncatable_prime( *p, sieve ) ) {
      count++;
      sum += *p;
    }
  }
  cout << "there are " << count << " truncatable primes below " << limit << " and their sum is " << sum << endl;
}
