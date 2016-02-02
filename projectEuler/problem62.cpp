/*
The cube, 41063625 (345^3), can be permuted to produce two other
cubes: 56623104 (384^3) and 66430125 (405^3). In fact, 41063625 is the
smallest cube which has exactly three permutations of its digits which
are also cube.

Find the smallest cube for which exactly five permutations of its
digits are cube.
*/

#include "bigint.h"
#include <iostream>
#include <map>
#include <string>
#include <stdlib.h>
#include <limits.h>
#include <sstream>
#include <algorithm>

using namespace std;

class counter
{
public:
  counter() : count(0), value(LLONG_MAX) {};
  counter( int c, long long v ) : count(c), value(v) {};
  int count;
  long long value;
};

// return the digits in smallest to largest order
string get_lowest_digits(long long i)
{
  ostringstream os;
  os << i;
  string s = os.str();
  sort(s.begin(), s.end());
  return s;
}

int main(int argc, char* argv[])
{
  long long i;
  long long upper_limit = 2097152; // cube root of long long max
  int match = 5;
  if ( argc > 1 ) {
    upper_limit = atol(argv[1]);
  }
  if ( argc > 2 ) {
    match = atoi(argv[2]);
  }

  map<string,counter> cube_counter;

  for ( i = 2; i < upper_limit; i++ ) {
    long long cube = i*i*i;
    string s = get_lowest_digits(cube);

    counter & counter = cube_counter[s];
    cout << i << " " << cube << " " << s << " " << counter.count << " " << counter.value << endl;
    counter.count++;
    counter.value = min(counter.value,cube);
    if ( counter.count == match ) {
      cout << counter.value << endl;
      break;
    }
  }
}
