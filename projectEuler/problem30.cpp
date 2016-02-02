/*
Surprisingly there are only three numbers that can be written as the
sum of fourth powers of their digits:

1634 = 1^4 + 6^4 + 3^4 + 4^4
8208 = 8^4 + 2^4 + 0^4 + 8^4
9474 = 9^4 + 4^4 + 7^4 + 4^4

As 1 = 1^4 is not a sum it is not included.

The sum of these numbers is 1634 + 8208 + 9474 = 19316.

Find the sum of all the numbers that can be written as the sum of
fifth powers of their digits.  

*/

#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

long long power( long long i, int pow )
{
  long long res = i;
  for (int j = 1; j < pow; j++ ) {
    res *= i;
  }
  return res;
}

long long sum_power_of_digits( long long i, int pow )
{
  ostringstream os;
  os << i;
  const string &s = os.str();
  long long sum = 0;
  for (string::const_iterator c = s.begin(); c != s.end(); c++) {
    int p = power( *c - '0', pow ); 
    // cout << *c - '0' << "^" << pow << " = " << p << endl;
    sum += p;
  }
  // cout << "the sum of the digits of " << i << " to the power " << pow << " is " << sum << endl;
  return sum;
}

int main(int argc, char* argv[])
{
  long long limit = 10000;
  int power = 5;
  if ( argc > 1 ) {
    limit = atol(argv[1]);
    if ( argc > 2 ) {
      power = atoi(argv[2]);
    }
  }

  // start at 2^5
  long long sum = 0;
  for (long long i = 32; i < limit; i++) {
    if ( i == sum_power_of_digits( i, power ) ) {
      cout << i << " is the sum of its digits to the power " << power << endl;
      sum += i;
    }
  }
  cout << "the sum of the numbers that can be written as the sum of their digits to the power " << power << " is " << sum << endl;
}
