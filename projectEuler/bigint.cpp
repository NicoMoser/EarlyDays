#include "bigint.h"
#include <vector>
#include <ostream>
#include <stdio.h>

using namespace std;

ostream & operator << (ostream& os , BigInt const & num )
{
  vector<unsigned char>::const_reverse_iterator rit;
  for (rit = num.m_num.rbegin(); rit < num.m_num.rend(); ++rit){
    os << static_cast<int>(*rit);
  }
  return os;
}

BigInt::BigInt(const BigInt& n) : m_num(n.m_num)
{
}

BigInt& BigInt::operator=(const BigInt& num)
{
  m_num = num.m_num;
  return *this;
}

BigInt::BigInt(unsigned int i)
{
  unsigned int t;
  while (i) {
    t = i%10;
    m_num.push_back(t);
    i /= 10;
  }
}

long long BigInt::sumDigits()
{
  long long s = 0;
  for (size_t i = 0; i< m_num.size(); i++) {
    s += m_num[i];
  }
  return s;
}

void BigInt::timesTwo()
{
  int t, carry = 0;

  for ( int i = 0; i < m_num.size(); i++ ) {
    t = m_num[i];       // current digit
    t*=2;               // double it
    t += carry;
    carry = t/10;       // get the future carry
    t -= carry*10;
    m_num[i] = t;
  }
  if ( carry ) {
    m_num.push_back(carry);
  }
}


BigInt add_short_to_long(const BigInt& a, const BigInt& b)
{
  BigInt num(b);
  // a is not longer than b
  int m = a.m_num.size();
  int carry = 0;
  for (int i=0; i<m; i++) {
    int ta = a.m_num[i];
    int tb = b.m_num[i];
    int t = ta + tb + carry;
    carry = t/10;
    t -= carry*10;
    num.m_num[i] = t;
  }

  int M = b.m_num.size();
  int t;
  if (M == m) {
    while (carry) {
      t = carry;
      carry = t/10;
      t-=carry*10;
      num.m_num.push_back(t);
    }
    return num;
  }

  for (int i=m; i < num.m_num.size(); i++ ) {
    t = num.m_num[i];
    t += carry;
    carry = t/10;
    t -= carry*10;
    num.m_num[i] = t;
  }
  if ( carry ) {
    num.m_num.push_back(carry);
  }
  return num;
}

BigInt& BigInt::operator+=(const BigInt& a)
{
  BigInt b(*this);
  *this = a + b;
  return *this;
}

BigInt operator+(const BigInt& a, const BigInt& b)
{
  if ( a.m_num.size() < b.m_num.size() ) {
    return add_short_to_long( a, b );
  } else {
    return add_short_to_long( b, a );
  }
}

BigInt & BigInt::operator*=(int n)
{
  // doesn't handle very large values of n - no overflow check
  int t, carry = 0;

  for ( int i = 0; i < m_num.size(); i++ ) {
    t = m_num[i];       // current digit
    t*=n;               // multiply it - overflow warning
    t += carry;         // bring over carry from previous place - more overflow warning
    carry = t/10;       // get the future carry
    t -= carry*10;      // should be less than 10, by construction
    m_num[i] = t;       // assign to current position
  }
  while ( carry ) {
    t = carry;
    carry = t/10;
    t -= carry*10;
    m_num.push_back(t);
  }
  return *this;
}

BigInt operator*(const BigInt& b, int n)
{
  BigInt a(b);
  // doesn't handle very large values of n - no overflow check
  int t, carry = 0;

  for ( int i = 0; i < a.m_num.size(); i++ ) {
    t = a.m_num[i];     // current digit
    t*=n;               // multiply it - overflow warning
    t += carry;         // bring over carry from previous place - more overflow warning
    carry = t/10;       // get the future carry
    t -= carry*10;      // should be less than 10, by construction
    a.m_num[i] = t;     // assign to current position
  }
  while ( carry ) {
    t = carry;
    carry = t/10;
    t -= carry*10;
    a.m_num.push_back(t);
  }
  return a;
}

size_t BigInt::size() const
{
  return m_num.size();
}


