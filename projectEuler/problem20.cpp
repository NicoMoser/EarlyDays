/*
n! means n x (n - 1)x  ... x 3 x 2 x 1

For example, 10! = 10 x 9 x ... x 3 x 2 x 1 = 3628800,
and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

Find the sum of the digits in the number 100!
*/

#include "bigint.h"
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[])
{
  int n = 100;
  if (argc > 1) {
    n = atoi(argv[1]);
  }

  BigInt a(n);

  BigInt b(a);
  for (int m=n-1; m > 1; m--) {
    b = a*m;
    a = b;
  }

  cout << n << "!=" << a << endl;
  cout << "the sum of the digits of " << n << "!=" << a.sumDigits() << endl;
  return 0;
}

