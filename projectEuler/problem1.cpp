/*
If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of 3 or 5 below 1000.
*/

#include <iostream>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  if ( argc < 2 ) {
    std::cout << argv[0] << " M" << std::endl
	      << "prints the sum of multiples of 3 or 5 less than M." << std::endl;
    return 1;
  }
  int M = atoi(argv[1]);
  unsigned int s = 0;
  for (int i=3; i<M; i++)
    {
      if ( 0 == i%3 || 0 == i%5 )
	{
	  s += i;
	}
    }
  std::cout << "sum of multiples of 3 or 5 less than " << M << " = " << s << std::endl;
  return 0;
}
