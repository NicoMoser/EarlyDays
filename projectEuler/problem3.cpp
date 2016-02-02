/*
The prime factors of 13195 are 5, 7, 13 and 29.

What is the largest prime factor of the number 600851475143
*/

/*
  try every odd number - although it's wasteful, it's simpler than
  trying to figure out the next prime to try - and probably faster.
 */
#include <iostream>

int main(int argc, char *argv[])
{
  long long composite = 600851475143LL;
  long long t = 3;
  long long last;
  for (t=3;t*t<=composite;t+=2)
    {
      if ( 0 == composite % t )
	{
	  last = t;
	}
    }
  std::cout << composite << std::endl;
  std::cout << last << std::endl;
  return 0;
}
