/*
An irrational decimal fraction is created by concatenating the
positive integers:

0.123456789101112131415161718192021...

It can be seen that the 12th digit of the fractional part is 1.

If d_n represents the nth digit of the fractional part, find the value
of the following expression.

d_1 × d_10 × d_100 × d_1000 × d_10000 × d_100000 × d_1000000

digits   count      total length
1        9                9
2        90 (10-99)     189
3        900 (100-999) 2889
4        9000         38889
5        90000       488889
6        900000     5888889

echo $((900*3 + 90*2 + 9 + 9000*4 + 90000*5 + 900000*6))

*/

