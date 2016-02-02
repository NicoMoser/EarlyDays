/*

The fraction 49/98 is a curious fraction, as an inexperienced
mathematician in attempting to simplify it may incorrectly believe
that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

There are exactly four non-trivial examples of this type of fraction,
less than one in value, and containing two digits in the numerator and
denominator.

If the product of these four fractions is given in its lowest common
terms, find the value of the denominator.

16/64
19/95
26/65
49/98

reduced fractions are
1/4 * 1/5 * 2/5 * 1/2 = 1/4 * 1/5 * 1/5 = 1/100
*/

#include <iostream>

using namespace std;

bool naive_cancels( int num, int den )
{
  // for each non-zero common digit in num and den compute n and d,
  // which are num and den with the common digit removed,
  // respectively.  no common digits => return false

  int n, d;

  int num_units, num_tens, den_units, den_tens;
  num_units = num % 10;
  den_units = den % 10;

  num_tens = num / 10;
  den_tens = den / 10;

  if ( num_units == den_units && den_units ) {
    n = num_tens;
    d = den_tens;
  } else if ( num_units == den_tens && den_tens ) {
    n = num_tens;
    d = den_units;
  } else if ( num_tens == den_units && den_units ) {
    n = num_units;
    d = den_tens;
  } else if ( num_tens == den_tens && den_tens ) {
    n = num_units;
    d = den_units;
  } else {
    // no common digits
    return false;
  }


  return (n*den == d*num);
}

int main(int argc, char* argv[])
{
  int N = 1, D = 1;
  for (int num = 11; num <= 98; num++) {
    for (int den = num + 1; den <= 99; den++) {
      if ( naive_cancels( num, den ) ) {
	cout << num << "/" << den << endl;
	N *= num;
	D *= den;
      }
    }
  }
  cout << N << "/" << D << endl;
}
