#include <vector>
#include <ostream>

// unsigned for now
class BigInt
{
  friend std::ostream& operator<<(std::ostream &,const BigInt&);
  friend BigInt operator +(const BigInt&, const BigInt&);
  friend BigInt operator *(const BigInt&, const BigInt&);
  friend BigInt operator *(const BigInt&, int);
  friend BigInt add_short_to_long(const BigInt& a, const BigInt& b);

public:
  BigInt(unsigned int);
  BigInt(const BigInt&);
  BigInt& operator=(const BigInt&);
  BigInt& operator+=(const BigInt&);
  BigInt& operator *= (int);
  void timesTwo();
  long long sumDigits();
  size_t size() const;
private:
  std::vector<unsigned char> m_num; // store in reverse order to display order
};

BigInt operator +(const BigInt&, const BigInt&);

std::ostream& operator<<(std::ostream& os, BigInt const & num);


