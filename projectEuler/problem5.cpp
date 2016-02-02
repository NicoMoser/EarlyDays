/*
2520 is the smallest number that can be divided by each of the numbers
from 1 to 10 without any remainder.

What is the smallest positive number that is evenly divisible by all
of the numbers from 1 to 20?
*/

/*
  this solution is pretty slow

  the answer is simply 16*5*7*9*11*13*17*19 - take the highest powers
  of the prime factors that appear - e.g. 16 = 2**4, which includes lower powers of 2.
*/

#include <iostream>

int main(int argc, char* argv[])
{
  int i = 20;
  for (;;i++) {
    bool is_evenly_divisible = true;
    for ( int j=1; is_evenly_divisible && j<=20; j++ ) {
      if ( i%j ) {
	is_evenly_divisible = false;
      }
    }
    if (is_evenly_divisible) {
      break;
    }
  }
  std::cout << i << " is the smallest positive number evenly divisible by all the numbers from 1 to 20" << std::endl;
  return 0;
}
