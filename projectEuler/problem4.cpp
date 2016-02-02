/*
A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

Find the largest palindrome made from the product of two 3-digit numbers.
*/
#include <string>
#include <iostream>
#include <sstream>

bool is_palindrome(const std::string& s)
{
  std::string::const_iterator start = s.begin();
  std::string::const_iterator end = s.end() - 1;
  while (start < end)
    {
      if ( *start++ != *end-- ) return false;
    }

  return ( *start == *end );
}

int main(int argc, char *argv[])
{
  int i, j, m = 0;
  for (i=100;i<999;i++)
    {
      for (j=i+1;j<1000;j++)
	{
	  std::ostringstream os;
	  os << i*j;
	  if (is_palindrome(os.str()))
	    {
	      //	      std::cout << i << "*" << j << "=" << os.str() << " is a palindrome" << std::endl;
	      m=std::max(m,i*j);
	    }
	}
    }
  std::cout << "largest palindrome of 3 digit numbers = " << m << std::endl;
  return 0;
}
