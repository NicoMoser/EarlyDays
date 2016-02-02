/*

The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.

There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.

How many circular primes are there below one million?

*/


#include "primes.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>

using namespace std;

bool is_circular_prime( int p, const bitset<sieve_size> &sieve )
{
  ostringstream os;
  os << p;
  const string &s = os.str();

  // see std::rotate()

  const int n = s.length();
  for (int i=1; i<n; i++) {
    string rot = s.substr(i) + s.substr(0,i);
    int test = atol(rot.c_str());
    if ( !sieve[test] ) {
      return false;
    }
  }
  return true;
}

int main( int argc, char* argv[] )
{
  int limit = sieve_size;
  if ( argc > 1 ) {
    limit = atoi( argv[1] );
  }
  const vector<int> &primes = get_primes();
  const bitset<sieve_size> &sieve  = get_sieve();
  cout << "there are " << primes.size() << " primes " << endl;
  int count = 0;
  for ( vector<int>::const_iterator p = primes.begin(); p != primes.end() && *p < limit; ++p) {
    if ( is_circular_prime( *p, sieve ) ) {
      count++;
    }
  }
  cout << "there are " << count << " circular primes below " << limit << endl;
}
