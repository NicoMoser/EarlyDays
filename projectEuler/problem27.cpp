/*

Euler published the remarkable quadratic formula:

n² + n + 41

It turns out that the formula will produce 40 primes for the
consecutive values n = 0 to 39. However, when n = 40, 
40² + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 
41² + 41 + 41 is clearly divisible by 41.

Using computers, the incredible formula n² − 79n + 1601 was
discovered, which produces 80 primes for the consecutive values n = 0
to 79. The product of the coefficients, −79 and 1601, is −126479.

Considering quadratics of the form:

    n² + an + b, where |a| < 1000 and |b| < 1000

    where |n| is the modulus/absolute value of n
    e.g. |11| = 11 and |−4| = 4

Find the product of the coefficients, a and b, for the quadratic
expression that produces the maximum number of primes for consecutive
values of n, starting with n = 0.

*/

#include "primes.h"
#include <bitset>
#include <vector>
#include <iostream>

using namespace std;

int eval_poly( int a, int b, int n )
{
  return n*n + a*n + b;
}
// return the number of primes produced by the equation
// n² + an + b
// for n starting at 0.
int get_consecutive_primes( int a, int b, const bitset<sieve_size> &sieve )
{
  int n = 0;
  int y = eval_poly(a, b, n);
  // cout << "eval_poly( " << a << ", " << b << ", " << n << " ) = " << y << endl;
  while ( 0 <= y && y < sieve_size && sieve[y] ) {
    // cout << y << " is prime" << endl;
    n++;
    y = eval_poly(a, b, n);
  }
  // cout << "n² + an + b for a=" << a << " and b=" << b << " results in " << n << " consecutive primes" << endl;
  return n;
}

int main(int argc, char* argv[])
{
  const vector<int> &primes = get_primes();
  const bitset<sieve_size>& sieve = get_sieve();

  /* brute force: two nested loops of a, b from -1000 to +1000 
     for each pair a,b, determine how long is the sequence of primes created by 
     n² + an + b
     n starting at 0.
     keep track of the a, b pair (or its product) for the longest sequence
     note that b needs to be prime since the n=0 case must result in a prime.
  */

  long long max_product = 0;
  int max_consecutive_primes = 0;
  for (vector<int>::const_iterator b_it = primes.begin(); *b_it < 1000; ++b_it) {
    if ( distance(b_it, primes.begin()) % 100 == 0 ) {
      cout << "testing b = " << *b_it << endl;
    }
    for (int a=-1000; a<=1000; a++ ) {
      int consecutive_primes = get_consecutive_primes(a,*b_it, sieve);
      if ( consecutive_primes > max_consecutive_primes ) {
	max_consecutive_primes = consecutive_primes;
	max_product = a* (*b_it);
	cout << "n² + an + b for a=" << a << " and b=" << *b_it << " results in " << consecutive_primes << " consecutive primes" << endl;
      }

      consecutive_primes = get_consecutive_primes(a,-*b_it, sieve);
      if ( consecutive_primes > max_consecutive_primes ) {
	max_consecutive_primes = consecutive_primes;
	max_product = a* (-*b_it);
	cout << "n² + an + b for a=" << a << " and b=" << -*b_it << " results in " << consecutive_primes << " consecutive primes" << endl;
      }
    }
  }
  cout << "the product of the coefficients that produces a sequence of primes of length " << max_consecutive_primes << " is " << max_product << endl;
}
