/*
Triangle, pentagonal, and hexagonal numbers are generated by the
following formulae:

Triangle 	  	T_n=n(n+1)/2 	  	1, 3, 6, 10, 15, ...
Pentagonal 	  	P_n=n(3n−1)/2 	  	1, 5, 12, 22, 35, ...
Hexagonal 	  	H_n=n(2n−1) 	  	1, 6, 15, 28, 45, ...

It can be verified that T_285 = P_165 = H_143 = 40755.

Find the next triangle number that is also pentagonal and hexagonal.
*/

#include <math.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

// given a Triagonal number, T, see if there is an integer n, s.t. P(n) == T
int isPentagonal( int T )
{
  /*
    P(n) == T
    n*(3*n-1) == 2*T
    3n^2 - n - 2*T == 0
    has roots (-b +/- sqrt( b^2 - 4ac))/2a
    = (1 + sqrt(1+24*T))/6
    = (1 + 989)/6
    = 990/6 = 165

    check: T == 40755
    
   */

  double t = 1 + sqrt(1+24*T);
  long i = t;
  if ( (i - 1)*(i-1) == 1+24*T && i % 6 == 0 ) {
    return i/6;
  }
  return 0;
}

int isHexagonal( int T )
{
  // Hexagonal 	  	H_n=n(2n−1) 	  	1, 6, 15, 28, 45, ...
  /*
    H(n) == T
    n*(2*n-1) == T
    2n^2 - n - T == 0
    has roots (-b +/- sqrt( b^2 - 4ac))/2a
    = (1 + sqrt(1+8*T))/4

    check: T == 40755

    
   */

  double t = 1 + sqrt(1+8*T);
  long i = t;
  if ( (i - 1)*(i-1) == 1+8*T && i % 4 == 0 ) {
    return i/4;
  }
  return 0;
}

int main(int argc, char* argv[])
{
  /*
    Upper bound for i, j
    note that if T_i == P_j == H_k, i < j < k
    T_k = k*(k+1)/2 == P_j = j*(3*j-1)/2 == H_i = i*(2*i-1)

    k*k + k == 3*j*j - j == 4*i*i - 2*i

    j*j is approximately 1/3 k*k
    j is approximately sqrt(3)/3 k

    and i*i is approximately 3/4 j*j
    i is approximately sqrt(3)/2 * j

   */
  int limit = 10;
  if ( argc > 1 ) {
    limit = atoi(argv[1]);
  }

  for ( long long k = 1; k <= limit; ++k ) {
    long long T_k = k*(k+1)/2;
    int i, j;
    if ( (i = isPentagonal(T_k)) > 0 && (j = isHexagonal(T_k)) > 0 ) {
      cout << "T(" << k << ") = " << T_k << " = P(" << i << ") = H(" << j << ")" << endl;
    }
  }
  return 0;
}
