/*
An integer partition of a number n is a way of writing n as a sum of
positive integers.

Partitions that differ only in the order of their summands are
considered the same. A partition of n into distinct parts is a
partition of n in which every part occurs at most once.

The partitions of 5 into distinct parts are:
5, 4+1 and 3+2.

Let f(n) be the maximum product of the parts of any such partition of
n into distinct parts and let m(n) be the number of elements of any
such partition of n with that product.

So f(5)=6 and m(5)=2.

For n=10 the partition with the largest product is 10=2+3+5, which
gives f(10)=30 and m(10)=3.  And their product, f(10)·m(10) = 30·3 =
90

It can be verified that
∑f(n)·m(n) for 1 ≤ n ≤ 100 = 1683550844462.

Find ∑f(n)·m(n) for 1 ≤ n ≤ 10^14.
Give your answer modulo 982451653, the 50 millionth prime.

n  f(n)       m(n)
1   1  (1)     1
2   2  (2)     1
3   3  (3)     1
4   4  (4)     1
5   6  (3x2)   2
6   8  (4x2)   2
7  12  (4x3)   2
8  15  (5x3)   2
9  24  (4x3x2) 3
10 30  (5x3x2) 3
11 40  (5x4x2) 3
12 60  (5x4x3) 3
13 72  (6x4x3) 3
14 120 (5x4x3x2) 4
15 144 (6x4x3x2) 4
16 180 (6x5x3x2) 4
17 240 (6x5x4x2) 4
18 360 (6x5x4x3) 4
19 420 (7x5x4x3) 4
20 720 (6x5x4x3x2) 5 // now there's room to go down - put on the 2 and take one off the top
21 840 (7x5x4x3x2) 5
22 1008 (7x6x4x3x2) 5
23 1260 (7x6x5x3x2) 5
24 1680 (7x6x5x4x2) 5
25 2520 (7x6x5x4x3) 5
26 2880 (8x6x5x4x3) 5 // now have headroom
27 5040 (7x6x5x4x3x2) 6

when 4 is the smallest, the next one ends with 3x2

when 3 is the smallest, if there is no gap at the top, increase the
top. If there is a gap at the top, decrease the top and add a 2.

the 10^14 upper limit is not practical to do directly, even with
relatively quick ways to compute f(n) and m(n)

Maybe we can factor out expressions?

e.g. how many times does 2 appear in the sum? All of them except for
the last two steps of each length sequence. It seems there are 4 sequences of length 2, 5 of length 3, 6 of length 4, etc.

So we have 2*(2^2 + 3^3 + ...)

e.g. the sum is

1*1 +
2*1 +
3*1 +
4*1 +
(2*3)*2 +
(2*4)*2 +
(3*4)*2 +
(3*5)*2 +
(2*3*4)*3 +
(2*3*5)*3 +
(2*4*5)*3 +
(3*4*5)*3 +
(3*4*6)*3
...

*/

#include <list>
#include <iostream>
#include <stdlib.h>
#include <sstream>

using namespace std;

class DistinctPartition
{
  // it seems that
  // a partition consists of either two sequences of numbers
  // i_0, ..., i_n, j_0, ..., j_n
  // where the i's are 1 apart from each other and so are the j's
  // and i_n + 2 = j_0.
  // or one sequence of numbers (with no gap of more than 1).
  /*
    cases for the previous value, n:
    1) it has no gap: i_0, ..., k (i_0 is 2 or 3 for n > 4)
       insert gap at top: i_0, ..., k-1, k+1
       this obviously sums to n+1 - is it the maximum product?
       m(n+1) stays the same.
    2) there is a gap and it starts w/ 2: 2, ..., j-1, j+1, ..., k
       => 2, ..., j-2, j, j+1, ..., k
       
       j-2, j-1,    j+1
       j-2,      j, j+1
       
       m(n+1) stays the same
    3) there is a gap at the top and it starts w/ 3: 3, ..., k, k+2
       do the "insert a 2 and reduce the top" trick
       2, 3, ..., k, k+1
       m(n+1) goes up by one

       m(n) follows the sequence:
       1,1,1,1, 2,2,2,2, 3,3,3,3,3, 4,4,4,4,4,4, ...
       
   */
private:
  long long n; // should equal result of sum()
  long long len;
  int initial; // 1, ..., 4
  long long max_of_initial_sequence;
  // min_of_upper_sequence will either == max_of_initial_sequence, 
  // meaning there is no more
  // or == max_of_initial_sequence + 1,
  // meaning we look at max_of_upper_sequence
  long long min_of_upper_sequence; 
  long long max_of_upper_sequence;

public:
  DistinctPartition() :
    n(1),
    len(1),
    initial(1),
    max_of_initial_sequence(1),
    min_of_upper_sequence(1),
    max_of_upper_sequence(1)
  {
  }

  long long sum() {
    return n;
  }

  string display() {
    ostringstream os;
    os << initial;
    for (long long i = initial + 1; i <= max_of_initial_sequence; i++) {
      os << " " << i;
    }
    if ( min_of_upper_sequence > max_of_initial_sequence ) {
      for (long long i  = min_of_upper_sequence; 
	             i <= max_of_upper_sequence; i++) {
	os << " " << i;
      }
    }
    return os.str();
  }

  long long product(long long mod = 1) {
    long long s = 1;
    for (long long i = initial; i <= max_of_initial_sequence; ++i) {
      s *= i;
      if ( mod > 1 ) {
	s = s % mod;
      }
    }
    if ( min_of_upper_sequence > max_of_initial_sequence ) {
      for (long long i  = min_of_upper_sequence; 
	             i <= max_of_upper_sequence; ++i) {
	s *= i;
	if ( mod > 1 ) {
	  s = s % mod;
	}
      }
    }
    return s;
  }

  long long length() {
    return len;
  }

  void increment()
  {
    n++;
    if ( n < 5 ) {
      initial++;
      max_of_initial_sequence++;
      min_of_upper_sequence++;
      max_of_upper_sequence++;
      return;
    }

    if ( n == 5 ) {
      initial = 2;
      max_of_upper_sequence = min_of_upper_sequence = max_of_initial_sequence = 3;
      len = 2;
      return;
    }
    
    // case 1: no gap
    if ( max_of_initial_sequence == min_of_upper_sequence ) {
      // insert gap at top; upper sequence is 1 long
      max_of_initial_sequence--;
      min_of_upper_sequence++;
      max_of_upper_sequence++;
      return;
    }

    // case 2: there's a gap and sequence starts w/ 2
    if ( initial == 2 ) {
      if (max_of_initial_sequence == initial) {
	initial = 3;
	max_of_initial_sequence = max_of_upper_sequence;
	min_of_upper_sequence = max_of_initial_sequence;
      } else {
	max_of_initial_sequence--;
	min_of_upper_sequence--;
      }
      return;
    }

    if (initial == 3) {
      // case 3: there is a gap and sequence starts w/ 3
      // do the "insert a 2 and reduce the top" trick
      initial = 2;
      len++;
      max_of_upper_sequence--;
      max_of_initial_sequence = min_of_upper_sequence = max_of_upper_sequence;
      return;
    }
  }
};


int main(int argc, char* argv[])
{
  long long MOD = 982451653;

  long long limit = 100;
  if ( argc > 1 ) {
    limit = atoll(argv[1]);
    if ( argc > 2 ) {
      MOD = atoll(argv[2]);
    }
  }

  long long sum_of_products = 0;
  cout << "n\tf(n)\tm(n)\tf(n)*m(n)" << endl;

  DistinctPartition p;

  long long s = 0;
  for (long long i = 1; i <= limit; ++i) {
    long long prod = p.product(MOD);
    if ( MOD > 1 ) {
      s += (prod*p.length() % MOD);
      s = s % MOD;
    } else {
      s += prod*p.length();
    }
    if ( i % 10000 == 0 ) {
      cout << p.sum() << "\t" << prod << "\t" << p.length() << "\t" << ( MOD > 1 ? (prod*p.length()) % MOD : prod*p.length() ) << "\t" << s << endl; // " (" << p.display() << ")" << endl;
    }

    p.increment();
  }
  cout << "sum of products of f(n)m(n) for 1 ≤ n ≤ " << limit << ", mod " << MOD << " = " << s << endl;
}

