/*
The prime 41, can be written as the sum of six consecutive primes: 
41 = 2 + 3 + 5 + 7 + 11 + 13

This is the longest sum of consecutive primes that adds to a prime
below one-hundred.

The longest sum of consecutive primes below one-thousand that adds to
a prime, contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most
consecutive primes?

how to find sequences of primes that add up to other primes?
for each prime P (starting at the first prime below 1,000,000)
find the first two adjacent primes p_0, p_1 that sum to less than P.
continue adding adjacent primes until the sum is >= P.
Let N be the number of adjacent primes.
if sum == P
    map sum_length[P] = max( N, sum_length[P] )
else
    resume search from p_1

or
      
starting at the beginning of the vector, sum adjacent primes until the
sum exceeds 1,000,000.
    
each time a sum is a prime (use sieve to check), test the maximum
length of the sum and update it and the prime, if exceeded.

*/




#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <map>
#include <vector>

using namespace std;
int main(int argc, char* argv[])
{
  const int sieve_size = 1000000;
  bitset<sieve_size> sieve; // assume all are primes, slice them out otherwise
  for (int candidate=0;candidate < sieve_size; candidate++) {
    sieve[candidate]=true;
  }

  sieve[0] = sieve[1] = false;

  vector<int> primes;
  for (int candidate=0; candidate<sieve_size; candidate++) {
    if ( sieve[candidate] ) {
      primes.push_back(candidate);
      // "cross out" all the multiples of the prime
      for (int multiple=2; multiple*candidate < sieve_size; multiple++) {
	sieve[multiple*candidate] = false;
      }
    }
  }

  cout << "list of " << primes.size() << " primes" << endl;

  int sum_length = 0, prime;
  vector<int>::const_iterator p, q;
  int limit = 1;
  if ( argc > 1 ) {
    limit = atoi(argv[1]);
  }
  
  for (p = primes.begin(); p!=primes.end(); ++p) {
    cout << "testing sequences starting with " << *p << endl;
    int sum = *p;
    int count = 1;
    for ( q = p+1; q != primes.end(); ++q ) {
      sum += *q;
      count++;
      cout << "adding " << *q << " sum = " << sum << " count = " << count << endl;
      if ( sum > limit ) {
	cout << "sum is bigger than " << limit << endl;
	break;
      }

      if (sieve[sum]) {
	cout << sum << " is a prime" << endl;
	if (count > sum_length) {
	  cout << "new longest sequence length " << count << " starting at " << *p << " sums to prime " << sum << endl;
	  sum_length = count;
	  prime = sum;
	}
      }
    }
  }
  cout << "longest sequence length = " << sum_length << " adds up to prime " << prime << endl;
}

