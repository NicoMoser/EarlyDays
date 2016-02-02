/*
We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

What is the largest n-digit pandigital prime that exists?

note: 1,...,9 (and 1,...,8) sum to a multiple of 3, so 8 and 9 are not possible
pandigital primes. Same for 1,...,6 and 1,...,5

So try 1,...,7 and 1,...,4

note that the ones from 1,...,7 can't end in 2,4,5, or 6.
so we look at the 7-pandigitals ending in 1,3,7 - there are 6! = 720 of each.
*/

#include "primes.h"
#include "pandigital.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
  const vector<int>& primes = get_primes();
  cout << "there are " << primes.size() << " primes less than " << sieve_size << endl;

  vector<int>::const_reverse_iterator p;
  for ( p = primes.rbegin(); p != primes.rend(); ++p ) {
    if ( pandigital( *p ) ) {
      cout << *p << endl;
      break;
    }
  }
}

