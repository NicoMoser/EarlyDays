/*
The arithmetic sequence, 1487, 4817, 8147, in which each of the terms
increases by 3330, is unusual in two ways: (i) each of the three terms
are prime, and, (ii) each of the 4-digit numbers are permutations of
one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit
primes, exhibiting this property, but there is one other 4-digit
increasing sequence.

What 12-digit number do you form by concatenating the three terms in
this sequence?

list all the 4-digit primes - easy, primes between 1000 and 9999,
inclusive.

for each 4-digit prime, p, find all its permutations {p_1,...,p_23}

if p > p_i, for some i, exit.

for each p_i, compute p_i - p. If p_i -p == (p_j-p)*2 for some j < i,
then p, p_j, and p_i are the sequence.

*/

#include "primes.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>


using namespace std;

void reverse_to_end( vector<int> &v, size_t initial )
{
  size_t last = v.size() - 1;
  while ( initial < last ) {
    int tmp = v[last];
    v[last] = v[initial];
    v[initial] = tmp;
    initial++;
    last--;
  }
}

bool permute( vector<int> & v )
{
  size_t n = v.size();
  int l,k;
  k = n-2;
  while ( 0 <= k && v[k] >= v[k+1] ) {
    k--;
  }
  if ( k < 0 ) {
    return false;
  }

  l = n-1;

  while ( l < n && v[k] >= v[l] ) {
    l--;
  }

  int tmp = v[l];
  v[l] = v[k];
  v[k] = tmp;

  reverse_to_end(v,k+1);
  return true;
}

long long to_int(const vector<int> &v)
{
  long long s = 0;
  for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    s = 10*s + *it;
  }
  return s;
}

void display( const vector<int> & v )
{
  if ( v.empty() ) {
    cout << endl;
    return;
  }

  vector<int>::const_iterator it = v.begin();
  cout << *it;
  ++it;
    
  while (it != v.end()) {
    cout << " " << *it;
    ++it;
  }
  cout << endl;
}

bool permute_test(int p, const bitset<sieve_size>& primes)
{
  cout << "testing permutations of " << p << endl;
  int i = p;
  vector<int> v;
  while (i) {
    v.push_back(i%10);
    i /= 10;
  }
  reverse(v.begin(),v.end());
  //display(v);

  int diff = 0;
  int prev = p;
  vector<int> diffs;
  
  while (permute(v)) {
    long long q = to_int( v );
    if ( !primes[q] ) {
      // cout << q << " isn't prime" << endl;
      continue;
    }
    cout << q << " is prime" << endl;
    diff = q - prev;
    cout << q << " - " << prev << " = " << diff << endl;
    diffs.push_back(diff);
    size_t sz = diffs.size();
    if ( sz > 1 ) {
      if ( diffs[sz-2] == diffs[sz-1] ) {
	cout << "found it" << endl;
	return true;
      }
    }
    prev = q;
  }

  return false;
}

int main(int argc, char* argv[])
{
  const vector<int>& primes = get_primes();
  const bitset<sieve_size>& sieve = get_sieve();

  for (vector<int>::const_iterator it = primes.begin(); 
       it != primes.end(); 
       ++it) {
    if ( *it < 1000 ) {
      continue;
    }
    if ( permute_test(*it, sieve)) {
      return 0;
    }
  }
}
