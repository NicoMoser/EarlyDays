#include <iostream>
#include <sstream>
#include <stdint.h>
#include <vector>

std::string tenstostring(const unsigned long i)
{
  std::string s;
  //assert(i < 10);
  //assert(1 < i);
  if ( i >= 10)
    return std::string("xxx tenstostring i >= 10 xxx");
  if ( i <= 1 )
    return std::string("xxx tenstostring i <= 1 xxx");
  switch (i)
    {
    case 9: s = "ninety"; break;
    case 8: s = "eighty"; break;
    case 7: s = "seventy"; break;
    case 6: s = "sixty"; break;
    case 5: s = "fifty"; break;
    case 4: s = "forty"; break;
    case 3: s = "thirty"; break;
    case 2: s = "twenty"; break;
    default: s = ""; break;
    }
  return s;
}


std::string lessthantwentytostring(const unsigned long i)
{
  //assert(i<20);
  if ( i > 20 )
    return std::string("xxx lessthantwnetytostring i >= 20 xxx");
  std::string s;
  switch (i)
    {
    case 20: s = "twenty"; break;
    case 19: s = "nineteen"; break;
    case 18: s = "eighteen"; break;
    case 17: s = "seventeen"; break;
    case 16: s = "sixteen"; break;
    case 15: s = "fifteen"; break;
    case 14: s = "fourteen"; break;
    case 13: s = "thirteen"; break;
    case 12: s = "twelve"; break;
    case 11: s = "eleven"; break;
    case 10: s = "ten"; break;
    case 9:  s = "nine"; break;
    case 8:  s = "eight"; break;
    case 7:  s = "seven"; break;
    case 6:  s = "six"; break;
    case 5:  s = "five"; break;
    case 4:  s = "four"; break;
    case 3:  s = "three"; break;
    case 2:  s = "two"; break;
    case 1:  s = "one"; break;
    case 0:  s = ""; break;
    default: s = ""; break;
    }
  return s;
}

std::string numberstring(const unsigned long i)
{
  if( i < 20 )
    {
      return lessthantwentytostring(i);
    }
  else if ( i < 100 )
    {
      unsigned long tens;
      tens = i/10;
      return tenstostring(tens) + lessthantwentytostring(i - tens*10);
    }
  else if ( i < 1000 )
    {
      unsigned long hundreds;
      hundreds = i / 100;
      if ( i - hundreds*100 == 0 ) {
	return numberstring(hundreds) + "hundred" + numberstring(i - hundreds*100);
      } else {
	return numberstring(hundreds) + "hundredand" + numberstring(i - hundreds*100);
      }
    }
  else if ( i < 1000000 )
    {
      unsigned long thousands;
      thousands = i / 1000;
      return numberstring(thousands) + "thousand" + numberstring(i-thousands*1000);
    }
  else if ( i < 1000000000 )
    {
      long millions;
      millions = i / 1000000;
      return numberstring(millions) + "million" + numberstring(i-millions*1000000);
    }
}

int main(int argc, char* argv[])
{
  if (argc < 1) return 0;
  long i;
  long start = 1;
  long incr = 1;
  long end;
  bool newline = true;
  if ( argc < 2 )
    {
      std::cout << "Usage: " << argv[0] << "[<start>] [<end> [<incr>]]" << std::endl;
      return 1;
    }
  else if ( argc < 3 )
    {
      end = atoi(argv[1]);
      // if std::string overhead is too high
      // do this case "constructively"
      // i.e. just iteratively construct all these
      // numbers.
    }
  else if (argc < 4)
    {
      start = atoi(argv[1]);
      end = atoi(argv[2]);
    }
  else if (argc < 5)
    {
      start = atoi(argv[1]);
      end = atoi(argv[2]);
      incr = atoi(argv[3]);
    }
  else
    {
      start = atoi(argv[1]);
      end = atoi(argv[2]);
      incr = atoi(argv[3]);
      newline = argv[4][0] =='n'; 
    }

  for (i = start; i < end; i += incr ){
    std::cout << numberstring(i);
    if (newline) std::cout << std::endl;
  }

  return 0;
}

