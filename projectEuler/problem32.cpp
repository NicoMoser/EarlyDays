/*

We shall say that an n-digit number is pandigital if it makes use of
all the digits 1 to n exactly once; for example, the 5-digit number,
15234, is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 x 186 = 7254,
containing multiplicand, multiplier, and product is 1 through 9
pandigital.

Find the sum of all products whose multiplicand/multiplier/product
identity can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to
only include it once in your sum.

strategy 

if the product were 4 digits long, it would mean the multiplicands
were 6 digits total, but 2 digits times 4 digits makes at least 6 digits:

10 x 10,000 = 100,000

while 3 and 3 makes at least 5 digits:

100 x 100 = 10000

so the product must be 5 or more digits.

Can it be 6 digits?

Can we make 6 digits out of two multiplicands with a total of 4 digits?

9 x 999 = 8,991

99 x 99 = 9801

no

So we're looking at 5 digits worth whose product is 5 digits

Can it be 1 and 4? Maybe:

9 x 8765 = 78,885

So we should check all pairs 1 and 4 digits long and all pairs 2 and 3 digits long

where none of the digits repeat.

*/

#include <iostream>
#include <set>

using namespace std;

bool is_pandigital_product( int m1, int m2, int product )
{
  bool ret = false;
  set<char> digits;

  while (m1 > 0) {
    char c = m1 %10;
    if ( 0 == c ) {
      return false;
    }
    if (digits.find(c) != digits.end()) {
      return false;
    }
    digits.insert(c);
    m1 /= 10;
  }

  while (m2 > 0) {
    char c = m2 %10;
    if ( 0 == c ) {
      return false;
    }
    if (digits.find(c) != digits.end()) {
      return false;
    }
    digits.insert(c);
    m2 /= 10;
  }

  while (product > 0) {
    char c = product %10;
    if ( 0 == c ) {
      return false;
    }
    if (digits.find(c) != digits.end()) {
      return false;
    }
    digits.insert(c);
    product /= 10;
  }
  return digits.size() == 9;
}

void pandigital_sum_1_4( set<int> &products )
{
  for (int m1 = 1; m1 < 10; m1++) {
    for (int m2 = 1234; m2 <= 9876; m2++) {
      // we should skip m2 if it contains one of the digits of m1
      // and come up with a better way to generate m2 so it doesn't duplicate its own digits.
      int product = m1*m2;
      if ( is_pandigital_product( m1, m2, product ) ) {
	cout << m1 << " x " << m2 << " = " << product << " is pandigital" << endl;
	products.insert(product);
      }
    }
  }
}

void pandigital_sum_2_3( set<int> & products)
{
  for (int m1 = 11; m1 <= 98; m1++) {
    for (int m2 = 123; m2 <= 987; m2++) {
      // we should skip m2 if it contains one of the digits of m1
      // and come up with a better way to generate m2 so it doesn't duplicate its own digits.
      int product = m1*m2;
      if ( is_pandigital_product( m1, m2, product ) ) {
	cout << m1 << " x " << m2 << " = " << product << " is pandigital" << endl;
	products.insert(product);
      }
    }
  }
}

int pandigital_sum()
{
  set<int> products;
  pandigital_sum_1_4(products);
  pandigital_sum_2_3(products);
  int sum = 0;
  for (set<int>::iterator p = products.begin(); p != products.end(); ++p) {
    sum += *p;
  }
  return sum;
}

int main(int argc, char* argv[])
{
  int sum = pandigital_sum();
  cout << "sum of pandigital products = " << sum << endl;
}
