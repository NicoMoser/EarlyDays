/*
The number, 1406357289, is a 0 to 9 pandigital number because it is
made up of each of the digits 0 to 9 in some order, but it also has a
rather interesting sub-string divisibility property.

Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way,
we note the following:

    * d2 d3 d4=406 is divisible by 2
    * d3 d4 d5=063 is divisible by 3
    * d4 d5 d6=635 is divisible by 5
    * d5 d6 d7=357 is divisible by 7
    * d6 d7 d8=572 is divisible by 11
    * d7 d8 d9=728 is divisible by 13
    * d8 d9 d10=289 is divisible by 17

Find the sum of all 0 to 9 pandigital numbers with this property.

There are 10! = 432000 0-9 pandigitals

d4 must be even
d6 is 0 or 5

for each 10! permutations, check the property above

*/

#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

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

bool property43(const vector<int>& v)
{
  return ( ( 0 == (100*v[7] + 10*v[8] + v[9]) % 17 ) &&
	   ( 0 == (100*v[6] + 10*v[7] + v[8]) % 13 ) &&
	   ( 0 == (100*v[5] + 10*v[6] + v[7]) % 11 ) &&
	   ( 0 == (100*v[4] + 10*v[5] + v[6]) % 7 ) &&
	   ( 0 == (100*v[3] + 10*v[4] + v[5]) % 5 ) &&
	   ( 0 == (100*v[2] + 10*v[3] + v[4]) % 3 ) &&
	   ( 0 == (100*v[1] + 10*v[2] + v[3]) % 2 ) );
}

long long to_int(const vector<int> &v)
{
  long long s = 0;
  for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    s = 10*s + *it;
  }
  return s;
}

int main(int argc, char* argv[])
{
  vector<int> nums;
  int limit = 10;
  if ( argc > 1 ) {
    limit = atoi(argv[1]);
  }
  nums.resize(limit);
  for (int i=0; i<limit; i++) {
    nums[i] = i;
  }

  long long sum = 0;
  do {
    if ( property43(nums) ) {
      long long i = to_int(nums); 
      sum += i;
      cout << "to_int = " << i << endl;
      display(nums);
    }
  }
  while ( permute(nums) );
  cout << "sum = " << sum << endl;
  return 0;
}
