/*

The decimal number, 585 = 1001001001 (binary), is palindromic in both
bases.

Find the sum of all numbers, less than one million, which are
palindromic in base 10 and base 2.

(Please note that the palindromic number, in either base, may not
include leading zeros.)

*/

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
using namespace std;

bool is_palindrome(int i)
{
  if ( i % 10 == 0 ) {
    // can't have leading zeros in the number
    return false;
  }
  stringstream os;
  os << i;
  string s = os.str();
  reverse(s.begin(), s.end());
  return (s == os.str());
}

bool is_palindrome_base_2(int i)
{
  if ( i % 2 == 0 ) {
    // can't have leading zeros in the number
    return false;
  }
  string s;
  while (i) {
    if ( i % 2 ) {
      s += "1";
    } else {
      s += "0";
    }    
    i /= 2;
  }
  string r = s;
  reverse(r.begin(), r.end());
  
  return r == s;
}

int main( int argc, char* argv[] )
{
  int limit = 1000000;
  if (argc > 1) {
    limit = atoi( argv[1] );
  }

  int sum = 0;
  for (int i=1; i<limit; ++i) {
    if ( is_palindrome(i) && is_palindrome_base_2(i) ) {
      sum += i;
    }
  }
  cout << sum << endl;
}
