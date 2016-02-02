/*
The sum of the squares of the first ten natural numbers is,
1**2 + 2**2 + ... + 10**2 = 385

The square of the sum of the first ten natural numbers is,
(1 + 2 + ... + 10)**2 = 55**2 = 3025

Hence the difference between the sum of the squares of the first ten
natural numbers and the square of the sum is 3025 − 385 = 2640.

Find the difference between the sum of the squares of the first one
hundred natural numbers and the square of the sum.
*/

#include <iostream>
#include <stdlib.h>

unsigned long long sum_of_squares(unsigned int M)
{
  unsigned long long s = 0;
  for (unsigned int i=1; i<=M; i++)
    {
      s += i*i;
    }
  return s;
}
   
unsigned long long square_of_sum(unsigned int M)
{
  unsigned long long s = 0;
  for (unsigned int i=1; i<=M; i++)
    {
      s += i;
    }
  return s*s;
}
   
   int main(int argc, char* argv[])
{
  if ( argc < 2 )return 1;

  int m = atoi(argv[1]);
  unsigned long long sum = sum_of_squares(m);
  unsigned long long square = square_of_sum(m);
  std::cout << "sum of squares up to " << m << " = " << sum << std::endl;
  std::cout << "square of sum up to " << m << " = " << square << std::endl;
  std::cout << square - sum << std::endl;
}
