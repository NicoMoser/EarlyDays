/*
2**15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 2**1000?
*/

/*
  ideas

  logarithm?

  recursion?

  what is the relationship between the digits of 2**(n-1) and 2**n?

             sum of digits
  2**1 = 2       2
  2**2 = 4       4
  2**3 = 8       8
  2**4 = 16      7
  2**5 = 32      5
  2**6 = 64     10
  2**7 = 128    11
  2**8 = 256    13
  2**9 = 512     8
  2**10 = 1024   7
  2**11 = 2048  14
  2**12 = 4096  19
  2**13 = 8192  20
  2**14 = 16384 22
  2**15 = 32768 26

  2**n = k_0*10**0 + k_1*10**1 + ...
 */

#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class MyNum
{
  friend ostream& operator<<(ostream &,const MyNum&);
public:
  MyNum(unsigned int);
  void timesTwo();
  long long sumDigits();
private:
  string m_num; // store in reverse order to display order
};

ostream & operator << (ostream& os , const MyNum & num )
{
  string s = num.m_num;
  size_t n = s.length() - 1;
  for (size_t i=0; i*2 <= n; i++){
    swap(s[i], s[n-i]);
  }
  
  os << s;
  return os;
}

MyNum::MyNum(unsigned int i)
{
  char buf[32] = {0};
  sprintf( buf, "%d", i );
  m_num = buf;
  size_t n = m_num.length() - 1;
  for (size_t i=0; i*2 <= n; i++){
    swap(m_num[i], m_num[n-i]);
  }
}

long long MyNum::sumDigits()
{
  long long s = 0;
  for (size_t i = 0; i< m_num.length(); i++) {
    s += m_num[i] - '0';
  }
  return s;
}

void MyNum::timesTwo()
{
  int t, carry = 0;

  for ( int i = 0; i < m_num.size(); i++ ) {
    t = m_num[i] - '0'; // current digit
    t*=2;               // double it
    t += carry;
    carry = t/10;       // get the future carry
    t -= carry*10;
    m_num[i] = '0' + t;
  }
  if ( carry ) {
    m_num += '0' + carry;
  }
}

int main(int argc, char* argv[])
{
  int power = 0;
  if ( argc > 1 ) {
    power = atoi(argv[1]);
  }
  MyNum myNum(1);
  // 
  for ( int i = 0; i < power; i++) {
    myNum.timesTwo();
  }
  cout << myNum << endl;
  cout << myNum.sumDigits() << endl;
  return 0;
}
