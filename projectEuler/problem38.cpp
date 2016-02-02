/*

Take the number 192 and multiply it by each of 1, 2, and 3:

192  1 = 192
192  2 = 384
192  3 = 576

By concatenating each product we get the 1 to 9 pandigital,
192384576. We will call 192384576 the concatenated product of 192 and
(1,2,3)

The same can be achieved by starting with 9 and multiplying by 1, 2,
3, 4, and 5, giving the pandigital, 918273645, which is the
concatenated product of 9 and (1,2,3,4,5).

What is the largest 1 to 9 pandigital 9-digit number that can be
formed as the concatenated product of an integer with (1,2, ... , n)
where n > 1?


approach:
there are 9! = 362,880 9-digit pandigital numbers

starting at p = 1, we need the product (1,2,...,9) to produce the 
number 123456789 (the smallest)

for p=2, we get 2 4 6 8 10 <bzt!>

multiply by 1, 2, 3, ... until we either produce exactly the digits 1,...,9 or produce 0, or a duplicated digit.

If we produce exactly 1,...,9, we update our current maximum and print p and n.

*/


#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <set>
#include <vector>

using namespace std;

// return false if any digits are already there
// or if n includes a zero
bool update_digits( int n, set<int>& digits )
{
  int original = n;
  while (n>0) {
    int d = n%10;
    if (0==d) {
      cout << original << " contains a zero" << endl;
      return false;
    }
    if ( digits.find(d) != digits.end() ) {
      cout << original << " contains an already-seen digit " << d << endl;
      return false;
    }
    cout << "adding " << d << " to digits" << endl;
    digits.insert(d);
    n /= 10;
  }
  return true;
}

int vector_to_num(const vector<int>& v)
{
  ostringstream os;
  for ( vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
    os << *it;
  }
  return atoi(os.str().c_str());
}

bool pandigital(int p, int &n, int& result)
{
  vector<int> numbers;
  set<int> digits;
  if ( !update_digits( p, digits ) ) {
    return false;
  }
  numbers.push_back(p);
  int i;
  for (i = 2; ; i++) {
    numbers.push_back(i*p);
    if ( !update_digits(i*p,digits) ) {
      return false;
    }
    if ( digits.size() == 9 ) {
      break;
    }
  }
  n = i;
  result = vector_to_num(numbers);
  return true;
}

int main( int argc, char* argv[] )
{
  int limit = 987654321;
  if ( argc > 1 ) {
    limit = atoi(argv[1]);
  }

  int M = 0; // maximum pandigital number
  int n_max = 0, p_max = 0;
  for (int p = 1; p*2 <= limit; ++p) {
    int n;
    // compute n such that the concatenation of p*1, p*2, ..., p*n is 
    // a 1,...,9 pandigital
    // or return 0 if it's not possible
    int result;
    cout << "testing " << p << endl;
    if (pandigital(p,n,result)) {
      cout << p << "x (1,...," << n << ") produces the result " << result << endl;
      if ( result > M ) {
	n_max = n;
	p_max = p;
	M = result;
      }
      cout << "the maximum pandigital is " << M << " produced by p = " << p_max << " x (1,...," << n_max << ")" << endl;
    }
  }
  cout << "the maximum pandigital is " << M << " produced by p = " << p_max << " x (1,...," << n_max << ")" << endl;
}
