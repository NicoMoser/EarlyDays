/*
The following iterative sequence is defined for the set of positive
integers:

n ->  n/2 (n is even)
n ->  3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following
sequence:

13  -> 40  -> 20  10  5  16  8  4  2  1

It can be seen that this sequence (starting at 13 and finishing at 1)
contains 10 terms. Although it has not been proved yet (Collatz
Problem), it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
*/ 
#include <iostream>
#include <stdlib.h>

long long sequence_length( long long n )
{
  long long s = 0;
  while ( n != 1 ) {
    if ( n %2 == 0 ) {
      n = n/2;
    } else {
      n = 3*n + 1;
    }
    s++;
  }
  return s;
}

int main(int argc, char* argv[])
{
  if ( argc < 2 ){
    std::cout << argv[0] << " m" << std::endl
	      << " compute the length of the sequences starting at m" << std::endl;
    return 1;
  }
  long long start = atol(argv[1]);

  long long max_sequence_length = 0;
  long long starting_point = start;
  for ( long long i = start; i < 1000000; i++ ) {
    long long s = sequence_length(i);
    if ( max_sequence_length < s ) {
      max_sequence_length = s;
      starting_point = i;
      std::cout << "starting at " << starting_point << " has a sequence length of " << max_sequence_length << std::endl;
    }
  }
  std::cout << "starting at " << starting_point << " has a sequence length of " << max_sequence_length << std::endl;
}
