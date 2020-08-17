/*
Consider the fraction, n/d, where n and d are positive integers. If n<d and HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d ≤ 8 in ascending order of size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7, 3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that there are 3 fractions between 1/3 and 1/2.

How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper fractions for d ≤ 12,000?
*/
#include <stdlib.h>
#include <iostream>
#include <stdlib.h>
#include "gcd.h"

using namespace std;

int main(int argc, char* argv[])
{
    long long count = 0;
    const long long denominator = 12000;
    
    for (long long i = 1; i <= denominator; i++)
    {
        for (long long j = 1; j<i; j++)
        {
            //cout << j << "/" << i << " is a proper fraction" << endl;
            if (2*j < i &&
              i < 3*j )
            {
                if ( (gcd(i,j) == 1))
                {
                   count++;
                }
            }
        }
    }

    cout << "There are " << count
         << " proper fractions between 1/3 and 1/2 with denominator <= "
         << denominator << endl;

    return 0;
}
