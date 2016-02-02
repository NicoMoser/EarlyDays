/*
Let d(n) be defined as the sum of proper divisors of n (numbers less
than n which divide evenly into n).

If d(a) = b and d(b) = a, where a != b, then a and b are an amicable
pair and each of a and b are called amicable numbers.

For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20,
22, 44, 55 and 110; therefore d(220) = 284. The proper divisors of 284
are 1, 2, 4, 71 and 142; so d(284) = 220.

Evaluate the sum of all the amicable numbers under 10000.

sum{ i : d(d(i)) == i and i < 10,000 }
*/

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

int d(int n)
{
  int s = 0;
  cout << "divisors of " << n << ":";
  for (int i = 1; 2*i <= n; i++) {
    if ( n % i == 0 ) {
      cout << i << " ";
      s += i;
    }
  }
  cout << ": sum = " << s << endl;
  return s;
}

int sum_amicable(int m)
{
  vector<int> D;
  D.reserve(m);
  D[0] = 0;
  D[1] = 0;
  for (int i=2; i<m; i++) {
    D[i] = d(i);
  }
  int s = 0;
  for (int i = 0; i < m; ++i) {
    int x= D[i];
    if ( x < m ) {
      // cout << "d(d(" << i << "))=" << D[x];
      if ( D[x] == i && i != x) {
	cout << i << endl;
	s += i;
      }
    }
  }
  return s;
}

int main(int argc, char* argv[])
{
  if ( argc < 2 ) {
    cout << argv[0] << " <n>" << endl
	 << " prints the sum of all amicable numbers under n" << endl;
    return 1;
  }
  int m = atoi(argv[1]);

  cout << sum_amicable(m) << endl;
  return 0;
}
