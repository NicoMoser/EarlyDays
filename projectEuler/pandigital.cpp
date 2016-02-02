#include "pandigital.h"

#include <bitset>
using namespace std;

bool pandigital(int p)
{
  bitset<9> digits(false);
  int count = 0;
  while ( p ) {
    int i = p % 10;
    if ( i == 0 ) {
      // zero - invalid digit
      return false;
    }
    if (digits[i-1]) {
      // duplicate digit
      return false;
    }
    digits[i-1] = true;
    p /= 10;
    count++;
  }
  // check if we missed any
  for (int i = 0; i < count; ++i) {
    if (!digits[i]) {
      return false;
    }
  }
  return true;
}
