/*

squares starting at n=1 (1x1)
squares are (2n-1)(2n-1) = 4n^2 -4n + 1 numbers

n=1
1x1 (2n-1)^2
1


n=2
add 4x(n) around edges
3x3
7 8 9
6 1 2
5 4 3

n=3
5x5 
21 22 23 24 25
20  7  8  9 10
19  6  1  2 11
18  5  4  3 12
17 16 15 14 13

7x7
43 44 45 46 47 47 49
42 21 22 23 24 25 26
41 20  7  8  9 10 27
40 19  6  1  2 11 28
39 18  5  4  3 12 29
38 17 16 15 14 13 30
37 36 35 34 33 32 31

ok, the upper-right diagonal appears to be the squares of the odd numbers
The lower-right diagonal
1 3 13 31
(1^2 - 0) (2^2 - 1) (4^2 - 3) (6^2-5) : conjecture (n-1)^2 - (n-2)

The lower-left diagonal
1 5 17 37
0^2+1 2^2+1 4^2+1 6^2+1 ...

Upper-left diagonal
1 7 21 43

formula:
16/3(n^3) -6n^2 +14/3n - 3, where n=501
yields 669171001

*/
