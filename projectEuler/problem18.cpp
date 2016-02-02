/*
By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

   3
  7 4
 2 4 6
8 5 9 3

That is, 3 + 7 + 4 + 9 = 23.


replace each value in the second row from the bottom by its sum of the largest value below it.
    3
  7  4
10 13 15

   3
 20 19

   23

Find the maximum total from top to bottom of the triangle below:

              75
             95 64
            17 47 82
           18 35 87 10
          20 04 82 47 65
         19 01 23 75 03 34
        88 02 77 73 07 63 67
       99 65 04 28 06 16 70 92
      41 41 26 56 83 40 80 70 33
     41 48 72 33 47 32 37 16 94 29
    53 71 44 65 25 43 91 52 97 51 14
   70 11 33 28 77 73 17 78 39 68 17 57
  91 71 52 38 17 14 91 43 58 50 27 29 48
 63 66 04 68 89 53 67 30 73 16 69 87 40 31
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23

NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route. However, Problem 67, is the same challenge with a triangle containing one-hundred rows; it cannot be solved by brute force, and requires a clever method! ;o)
*/

#include <iostream>
#include <vector>

using namespace std;

int find_best_path( vector< vector< int > > & rows )
{
  if ( rows.size() == 1 ) {
    return rows[0][0];
  }
  vector< vector<int> >::iterator row_it, lower_row;
  lower_row = row_it = rows.end() - 1;
  --row_it;
  vector<int>::iterator i, j;
  for (i=row_it->begin(), j=lower_row->begin(); i!=row_it->end(); ++i, ++j){
    *i += max(*j, *(j+1));
    cout << *i << " ";
  }
  cout << endl;
  rows.erase( lower_row );
  return find_best_path( rows );
}

int main(int argc, char* argv[])
{
  int numbers_per_row = 1;
  vector< vector<int> > rows;

  // there is something wrong here - on the sample data, this reads the last int
  // over and over.
  while (!cin.eof()) {
    vector<int> row;
    row.reserve(numbers_per_row);
    for (int j=0; j<numbers_per_row; j++) {
      int x;
      cin >> x;
      cout << " x=" << x;
      row.push_back(x);
    }
    cout << endl;
    rows.push_back(row);
    numbers_per_row++;
  }
  cout << find_best_path(rows) << endl;
}
