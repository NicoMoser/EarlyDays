/*
see also problem22 for scoring words

The nth term of the sequence of triangle numbers is given by, tn =
½n(n+1); so the first ten triangle numbers are:

1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

By converting each letter in a word to a number corresponding to its
alphabetical position and adding these values we form a word
value. For example, the word value for SKY is 19 + 11 + 25 = 55 =
t10. If the word value is a triangle number then we shall call the
word a triangle word.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text
file containing nearly two-thousand common English words, how many are
triangle words?

get each word, compute its score, s. Increment score_totals[s]. Update max_score and min_score.

For each triangle number, t, between min_score and max_score, accumulate score_totals[t].
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <map>
#include <limits.h>

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

int triangle(int i)
{
  return (i*(i+1))/2;
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
  //sort(names.begin(), names.end());

  map<int,int> scores;
  int m=INT_MAX, M=0;
  for (vector<string>::iterator it = names.begin(); it != names.end(); ++it ) {
    int s = score(*it);
    m=min(m,s);
    M=max(M,s);
    scores[s]++;
    //cout << *it << " " << s << " = " << s << endl;
  }
  // for (map<int,int>::const_iterator it=scores.begin(); it!=scores.end();++it) {
  //   cout << it->first << " " << it->second << endl;
  // }
  int i = 1;
  int t = triangle(i);
  int total = 0;
  while (t <= M) {
    if ( scores[t] ) {
      cout << "t = " << t << endl;
      total += scores[t];
    }
    i++;
    t = triangle(i);
  }
  cout << "total = " << total << endl;
}
