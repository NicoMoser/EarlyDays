/*
145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

Find the sum of all numbers which are equal to the sum of the
factorial of their digits.

Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

long long factorial_under_ten( unsigned long long i )
{
  switch(i) {
  case 0:
  case 1: return 1;
  case 2: return 2;
  case 3: return 6;
  case 4: return 24;
  case 5: return 120;
  case 6: return 720;
  case 7: return 7*720;
  case 8: return 8*7*720;
  case 9: return 9*8*7*720;
  default: return 0;
  }
}

long long sum_of_factorial_of_digits( long long i )
{
  char buf[64] = {0};

  snprintf( buf, sizeof(buf), "%d", i );
  char *p = buf;
  long long sum = 0;
  while (*p) {
    long long f = factorial_under_ten(*p - '0');
    sum += f;
    p++;
  }
  return sum;
}

int main(int argc, char* argv[])
{
  long long sum = 0;
  long long upper_limit = 1000;
  if ( argc > 1 ) {
    upper_limit = atol(argv[1]);
  }
  
  for (long long i=3; i <= upper_limit;i++) {
    long long f = sum_of_factorial_of_digits(i);
    if ( f == i ) {
      cout << i << endl;
      sum += i;
    }
  }
  cout << sum << endl;
}
