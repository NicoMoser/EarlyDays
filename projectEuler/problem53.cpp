/*
There are exactly ten ways of selecting three from five, 12345:

123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

In combinatorics, we use the notation, 5C3 = 10.

In general,

nCr = n!/r!(n-r)!, where r <= n, n! = n*(n-1)...3*2*1, and 0! = 1.

It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.

How many, not necessarily distinct, values of nCr, for 1 <= n <= 100, are 
greater than one-million?
*/


/*
  nCr is the r-th entry in the n-th row of Pascal's triangle
  even with long long, it overflows, however unsigned long long is sufficient
 */

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

int count_choices_less_than( int n, unsigned long long m )
{
  // initialize Pascal's triangle
  typedef vector<unsigned long long> row;
  typedef vector<row> triangle;
  triangle t;
  for (int i=0; i<=n; i++) {
    row v(i+1, 0);
    v[0] = 1;
    v[i] = 1; // ones along the sides
    t.push_back( v );
  }

  cout << "display" << endl;
  // display it
  for (triangle::const_iterator it = t.begin(); it != t.end(); ++it) {
    for ( row::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
      cout << *jt << " ";
    }
    cout << endl;
  }

  cout << "fill it in" << endl;
  // now fill it in
  for (int i=2; i<=n; i++) {
    for (int j=1; j<i; j++) {
      t[i][j] = t[i-1][j-1] + t[i-1][j];
    }
  }

  int count = 0;  
  for (triangle::const_iterator it = t.begin(); it != t.end(); ++it) {
    for ( row::const_iterator jt = it->begin(); jt != it->end(); ++jt) {
      cout << *jt << " ";
      if ( *jt > m ) {
	count++;
      }
    }
    cout << endl;
  }
  return count;
}

int main(int argc, char* argv[])
{
  int rows = 10;
  int max_val = 1000000;
  if ( argc > 1 ) {
    rows = atoi(argv[1]);
  }
  if ( argc > 2 ) {
    max_val = atoi(argv[2]);
  }
  int x = count_choices_less_than(rows, max_val);
  cout << x << endl;
}
