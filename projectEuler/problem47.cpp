/*
The first two consecutive numbers to have two distinct prime factors
are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime
factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct primes
factors. What is the first of these numbers?  

there will be two even and two odd numbers, so two of them will have 2
as a factor.


*/

#include "primes.h"
#include <vector>
#include <iostream>

using namespace std;

bool has_four_prime_factors( int n, const vector<int> &primes, vector<int> & factors)
{
  int factor_count = 0;
  vector<int>::const_iterator it;
  for (it = primes.begin(); (*it * 2) <= n; ++it ) {
    if ( n % *it == 0 ) {
      factor_count++;
      factors.push_back(*it);
      if (factor_count == 4) {
	return true;
      }
    }
  }
  return false;
}

int main( int argc, char* argv[] )
{
  cout << "making list of primes" << endl;
  const vector<int>& primes = get_primes();
  cout << "done" << endl;

  // first 4 primes are 2 3 5 7 whose product is 2*3*5*7 = 210 so this
  // is the smallest possible number with 4 distinct prime factors
  vector<int> factors1, factors2, factors3, factors4;
  for (int i = 210; ;) {
    // cout << "starting with " << i << endl;
    if ( has_four_prime_factors(i, primes, factors1) ) {
      cout << i << " has prime factors " << factors1[0] << " " << factors1[1]  << " " << factors1[2] << " " << factors1[3] << endl;
      i++;
      if ( has_four_prime_factors(i, primes, factors2) ) {
	cout << i << " has prime factors " << factors2[0] << " " << factors2[1]  << " " << factors2[2] << " " << factors2[3] << endl;
	i++;
	if ( has_four_prime_factors(i, primes, factors3) ) {
	  cout << i << " has prime factors " << factors3[0] << " " << factors3[1]  << " " << factors3[2] << " " << factors3[3] << endl;
	  i++;
	  if ( has_four_prime_factors(i, primes, factors4) ) {
	    cout << i << " has prime factors " << factors4[0] << " " << factors4[1]  << " " << factors4[2] << " " << factors4[3] << endl;
	    i++;
	    return 0;
	  } else {
	    i++;
	  }
	} else {
	  i++;
	}
      } else {
	i++;
      }
    } else {
      i++;
    }
  }
  return 1;
}
