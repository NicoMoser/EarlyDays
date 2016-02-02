/*
The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

Find the sum of all the primes below two million.
*/

#include <iostream>
#include <bitset>
#include <stdlib.h>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
  std::bitset<2000000> primes; // assume all are primes, slice them out otherwise
  for (int candidate=0;candidate < primes.size(); candidate++)
    primes[candidate]=true;

  primes[0] = primes[1] = false;

  for (int candidate=0; candidate*candidate<primes.size(); candidate++)
    {
      if ( primes[candidate] )
	{
	  //std::cout << candidate << " is prime" << std::endl;
	  // "cross out" all the multiples of the prime
	  for (int multiple=2; multiple*candidate < primes.size(); multiple++)
	    {
	      primes[multiple*candidate] = false;
	    }
	}
      else
	{
	  //std::cout << candidate << " is composite" << std::endl;
	}
    }

  long M = 2000000;
  if ( argc > 1 ) {
    M = atoi(argv[1] );
  }
  if (M == 0) M = 2000000;

  long long sum = 0;
  size_t counter = 0;
  int factor = 1;
  for (int candidate=0;candidate < M; candidate++)
    {
      if (primes[candidate]) {
	sum += candidate;
	counter++;
	if ( counter == 10001 ){
	  std::cout << "the 10001st prime = " << candidate << std::endl;
	}
	if ( 600851475143 % candidate == 0 ) {
	  factor = candidate;
	}
      }
    }

  std::cout << "the sum of the primes less than " << M << " is " << sum << std::endl;
  std::cout << "the largest prime factor of the number 600851475143 is " << factor << std::endl;

}
