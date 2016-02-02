/*

It can be seen that the number, 125874, and its double, 251748, contain
exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, 
contain the same digits.

*/

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

string get_digits(unsigned int x)
{
  string s;
  while ( x > 0 ) {
    s += '0' + x % 10;
    x /= 10;
  }
  sort(s.begin(), s.end());
  return s;
}

int main( int argc, char* argv[])
{
  for (unsigned int x = 1; ; ++x) {
    string s = get_digits(x);
    bool allmatch = true;
    for (unsigned int m = 2; m <= 6; ++m ) {
      if ( s != get_digits(x*m) ) {
	allmatch = false;
	break;
      }
    }
    if ( allmatch ) {
      cout << x << endl;
      break;
    }
  }
}
