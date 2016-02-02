/*
By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can
see that the 6th prime is 13.

What is the 10 001st prime number?
*/

#include <iostream>
#include <set>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  int candidate = 3;
  std::set<int> primes;
  primes.insert(2);

  if ( argc < 2 ) {
    std::cout << argv[0] << " M" << std::endl
	      << " prints the M-th prime" << std::endl;
    return 1;
  }
  int nth_prime = atoi(argv[1]);
  int last_prime = 2;
  while (primes.size() + 1 < nth_prime)
    {
      // if candidate is not divisible by anything in primes, add it to primes
      std::set<int>::iterator it;
      for (it=primes.begin(); it != primes.end(); ++it)
	{
	  if ( candidate % *it == 0 ) break;
	}
      if ( it == primes.end() )
	{
	  primes.insert(candidate);
	  last_prime = candidate;
	}
      candidate+=2;
    }
  std::cout << candidate<< std::endl;
}
