/*
Starting in the top left corner of a 2x2 grid, there are 6 routes
(without backtracking) to the bottom right corner.


How many routes are there through a 20x20 grid?
*/

#include <iostream>
#include <stdlib.h>


const int size = 21;
long long a[size][size] = {-1};

long long num_routes( long long i, long long j )
{
  if ( (i < 0) || (0 > j) || (i>=size) || (j>=size)) return 0;

  long long cache = a[i][j];
  if ( cache >= 0 ) {
    return cache;
  }

  if ( i == 0 || j == 0 ) {
    a[i][j] = 1;
    return 1;
  }

  long long left = num_routes(i-1,j);
  long long right = num_routes(i,j-1);

  a[i][j] = left + right;
  return a[i][j];
} 

int main(int argc, char* argv[])
{
  long long steps;
  if ( argc < 1 ) {
    std::cout << argv[0] << " size" << std::endl
	      << " prints the number of routes in a size x size grid" << std::endl;
    return 1;
  }
  steps = atoi( argv[1] );
  for (int i = 0; i < size; i++ ) {
    for (int j=0; j < size; j++ ) {
      a[i][j] = -1;
    }
  }
  std::cout << num_routes( steps, steps ) << std::endl;
}
