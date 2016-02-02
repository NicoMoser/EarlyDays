#include "primes.h"
#include <bitset>
#include <vector>

using namespace std;

static bitset<sieve_size> sieve;
static vector<int> primes;

static void make_lists()
{
  // assume all are primes, slice them out otherwise
  for (int candidate=0;candidate < sieve_size; candidate++) {
    sieve[candidate]=true;
  }

  sieve[0] = sieve[1] = false;

  for (int candidate=0; candidate<sieve_size; candidate++) {
    if ( sieve[candidate] ) {
      primes.push_back(candidate);
      // "cross out" all the multiples of the prime
      for (int multiple=2; multiple*candidate < sieve_size; multiple++) {
	sieve[multiple*candidate] = false;
      }
    }
  }
}

const bitset<sieve_size>& get_sieve()
{
  if ( primes.empty() ) {
    make_lists();
  }
  return sieve;
}

const vector<int>& get_primes()
{
  if ( primes.empty() ) {
    make_lists();
  }
  return primes;
}
