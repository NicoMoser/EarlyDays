/*
  A permutation is an ordered arrangement of objects. For example,
  3124 is one possible permutation of the digits 1, 2, 3 and 4. If all
  of the permutations are listed numerically or alphabetically, we
  call it lexicographic order. The lexicographic permutations of 0, 1
  and 2 are:

012   021   102   120   201   210

so for the permutations of 0,1,2,3 we have the first 6 starting with 0
the second 6 starting with 1, and so on.

What is the millionth lexicographic permutation of the digits 0, 1, 2,
3, 4, 5, 6, 7, 8 and 9?



9! = 362,880, which goes into 1,000,000 between 2 and 3 times.

The first 9! permutations start with 0, the second 9! start with
1. So the 1,000,000th is among those starting with 2 - the third available digit.

The 1st permutation is 0123456789, the 9!-th is 0987654321.
The 9!+1-th is 1023456789 and the 2*(9!)-th is 1987654320
The 2*(9!)+1-th is 2013456789

After skipping "0123456789" through "1987654320" (2*(9!)=725,760
permutations) there remain 274,240 more permutations until the
1,000,000th, which means somewhere between 6 and 7 times 8!=40,320

So the next digit is the 7th digit from the remaining 9 digits
(013456789), or 7.

so the first two digits are 
27, the remaining 8 digits are 01345689

We have accounted for 2*(9!) + 6*(8!) = 967,680 permutations, with
32,320 to go.

7!=5,040, which goes into 32,320 6 times with a remainder of 2080.

The 7th digit of the remaining is 8, so the permutation starts with
278 and the remaining digits are 0134569.

6!=720, which goes into 2,080 two times with a remainder of 640.  The
3rd digit of the remaining is 3. So the permutation starts with 2783
and the remaining digits are 014569.

5!=120, which goes into 640 5 times with a remainder of 40. The 6th
digit of the remaining is 9. So the permutation starts with 27839 and
the remaining digits are 01456.

4!=24 which goes into 40 once with a remainder of 16. The 2nd digit of
the remaining is 1. So the permutation starts with 278391 and the
remaining digits are 0456.

3!=6 which goes into 16 2 times with a remainder of 4. The 3rd
remaining digit is 5. So the permutation starts with 2783915 and the
remaining digits are 046.

2!=2 which goes into 4 2 times with a remainder of 0. The 3rd remaining
digit is 6 so the permutation is 2783915604.

rejected!

Last step - we want a reminder of 1 - 2! goes into 4 1 time with a remainder of 2.

The 2nd remaining digit is 4. So the permutation starts with

27839154 and ends with either 06 or 60

It ends with 60 (!)

*/

