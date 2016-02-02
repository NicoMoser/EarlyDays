/*
The Fibonacci sequence is defined by the recurrence relation:

    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

Hence the first 12 terms will be:

    F1 = 1
    F2 = 1
    F3 = 2
    F4 = 3
    F5 = 5
    F6 = 8
    F7 = 13
    F8 = 21
    F9 = 34
    F10 = 55
    F11 = 89
    F12 = 144

The 12th term, F12, is the first term to contain three digits.

What is the first term in the Fibonacci sequence to contain 1000 digits?
*/

#include "bigint.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
  BigInt F1(1), F2(1);
  BigInt F3 = F1 + F2;
  int limit = 3;
  if ( argc > 1 ) {
    limit = atoi(argv[1]);
  }
  int i = 3;
  while (F3.size() < limit) {
    cout << i << " | " << F3.size() << " | " << F3 << endl;
    F1 = F2;
    F2 = F3;
    F3 = F1 + F2;
    i++;
  }
  cout << i << " | " << F3.size() << " | " << F3 << endl;
}
