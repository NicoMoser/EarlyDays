/*

A perfect number is a number for which the sum of its proper divisors
is exactly equal to the number. For example, the sum of the proper
divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28
is a perfect number.

A number n is called deficient if the sum of its proper divisors is
less than n and it is called abundant if this sum exceeds n.

As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the
smallest number that can be written as the sum of two abundant numbers
is 24. By mathematical analysis, it can be shown that all integers
greater than 28123 can be written as the sum of two abundant
numbers. However, this upper limit cannot be reduced any further by
analysis even though it is known that the greatest number that cannot
be expressed as the sum of two abundant numbers is less than this
limit.

Find the sum of all the positive integers which cannot be written as
the sum of two abundant numbers.

approach:
bitset of integers sized 28123, initialized to false (assume it can't be written as a sum of two abundant numbers)

make a list of all the abundant numbers under some limit (28123 - 12)

for each unique pair of abundant numbers (a,b) where a<=b, set bitset[a+b] = true

sum the indices whose bitset value is false

 */

#include <iostream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <bitset>

using namespace std;

long long d(long long n)
{
  long long s = 0;
  //cout << "divisors of " << n << ":";
  for (long long i = 1; 2*i <= n; i++) {
    if ( n % i == 0 ) {
      //cout << i << " ";
      s += i;
    }
  }
  //cout << ": sum = " << s << endl;
  return s;
}

// return < 0 for "deficient" numbers
// return 0 for "perfect" numbers
// return > 0 for "abundant" numbers
long long quality( long long n )
{
  return d(n) - n;
}

int main( int argc, char* argv[])
{
  const int limit = 28123;
  bitset<limit> sum_of_two_abundant_numbers;
  for (int i = 0; i < limit; i++) {
    sum_of_two_abundant_numbers[i] = false;
  }

  vector<int> abundant_numbers;
  for (int i = 11; i < limit; i++ ) {
    if ( quality(i) > 0 ) {
      // cout << i << " is abundant" << endl;
      abundant_numbers.push_back(i);
    }
  }

  cout << "there are " << abundant_numbers.size() << " abundant numbers less than " << limit << endl;

  for (vector<int>::iterator a = abundant_numbers.begin(); 
       a != abundant_numbers.end(); 
       a++) {
    for (vector<int>::iterator b = a; 
	 b != abundant_numbers.end(); 
	 b++ ) {
      int sum_of_two = *a + *b;
      //cout << *a << " + " << *b << " = " << sum_of_two << "  is the sum of two abundant numbers" << endl;
      if (sum_of_two < limit) {
	sum_of_two_abundant_numbers[sum_of_two] = true;
      }
    }
  }

  long long sum = 0;
  for (int i = 0; i < limit; i++) {
    if ( !sum_of_two_abundant_numbers[i] ) {
      sum += i;
    }
  }

  cout << "the sum of all the positive integers that cannot be written as the sum of two abundant numbers is " << sum << endl;
}
