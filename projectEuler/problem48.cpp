/*

The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

*/

#include "bigint.h"
#include <sstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  BigInt I(0);
  ostringstream os;
  for (int i=1;i<=1000;i++) {
    cout << "adding " << i << "^" << i << endl;
    BigInt power(i);
    for (int j = 1; j<i; j++) {
      power *= i;
    }
    I += power;
    // cout << "I.size() = " << I.size() << endl;
  }
  os << I;
  long sz = I.size();
  string s = os.str().substr( sz-10 );
  cout << s << endl;
}
