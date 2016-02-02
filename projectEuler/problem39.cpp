/*

If p is the perimeter of a right angle triangle with integral length
sides, {a,b,c}, there are exactly three solutions for p = 120.

{20,48,52}, {24,45,51}, {30,40,50}

For which value of p ≤ 1000, is the number of solutions maximised?

*/

#include <stdlib.h>
#include <iostream>

using namespace std;

int num_solutions(int p)
{
  cout << "p=" << p << endl;
  int count = 0;
  for (int a = 3; a + 3 < p; ++a) {
    for ( int b = a + 1; a+b+3 < p; ++b ) {
      int c = p - (a+b);
      if ( c*c == b*b + a*a ) {
	cout << "a=" << a << " b=" << b << " c=" << c << endl;
	count++;
      }
    }
  }
  return count;
}

int main(int argc, char* argv[])
{
  int limit = 1000;
  if ( argc > 1 ) {
    limit = atoi(argv[1]);
  }

  int p_max_num_solutions = 12;
  int max_num_solutions = 0;
  for (int p = p_max_num_solutions; p <= limit; p++) {
    int num = num_solutions(p);
    if ( num > max_num_solutions ) {
      cout << p << " has " << num << " right angle solutions" << endl;
      p_max_num_solutions = p;
      max_num_solutions = num;
    }
  }
  cout << "p_max_num_solutions = " << p_max_num_solutions << endl;
}
