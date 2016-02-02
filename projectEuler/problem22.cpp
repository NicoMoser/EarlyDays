/*
Using names.txt (right click and 'Save Link/Target As...'), a 46K text
file containing over five-thousand first names, begin by sorting it
into alphabetical order. Then working out the alphabetical value for
each name, multiply this value by its alphabetical position in the
list to obtain a name score.

For example, when the list is sorted into alphabetical order, COLIN,
which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the
list. So, COLIN would obtain a score of 938 × 53 = 49714.

What is the total of all the name scores in the file?
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>

using namespace std;

void split_on_commas(const string& line, vector<string>& names)
{
  size_t s1 = 0, s2 = line.find(',');
  while (s2 != string::npos) {
    string s(line, s1, (s2-s1) );
    names.push_back( s );
    //cout << s << endl;
    s1 = s2 + 1;
    s2 = line.find(',', s1);
  }
  string s(line, s1);
  if ( s.length() > 0 ) {
    names.push_back( s );
    //cout << s << endl;
  }
}

int score(const string& s)
{
  int sum = 0;
  for ( string::const_iterator it = s.begin(); it != s.end(); ++it ) {
    if (isalpha(*it)) {
      // assume upper case
      sum += *it - 'A' + 1;
    }
  }
  return sum;
}

int main(int argc, char* argv[])
{
  if ( argc < 2 ) {
    cout << argv[0] << " <file>" << endl
	 << " prints the total of all the name scores in <file>" << endl
	 << " where the name score is the sum of the letters (A = 1, B = 2, ...) times the position in the sorted list" << endl;
    return 1;
  }

  ifstream ifs(argv[1]);
  if (!ifs.is_open()) {
    cout << "couldn't open " << argv[1] << endl;
    return 1;
  }
  vector<string> names;
  string line;
  while (ifs.good()) {
    getline(ifs, line);
    // cout << "read line of length " << line.length() << endl;
    split_on_commas(line, names);
  }
  // cout << "there are " << names.size() << " names" << endl;
  sort(names.begin(), names.end());

  int pos = 1;
  int total = 0;
  for (vector<string>::iterator it = names.begin(); it != names.end(); ++it ) {
    int s = score(*it);
    total += s*pos;
    cout << *it << " " << s << "*" << pos << " = " << s*pos << endl;
    pos++;
  }
  cout << "total = " << total << endl;
}
