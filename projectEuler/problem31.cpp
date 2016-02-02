/*
In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:

    1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).

It is possible to make £2 in the following way:

    1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p

How many different ways can £2 be made using any number of coins?
*/

#include <stdlib.h>
#include <iostream>

using namespace std;

int coin_count(int total)
{
  int count = 0;
  for (int i1 = 0; i1<=total; i1++) {
    if (i1 == total ) {
      cout << i1 << "x1p = " << total << endl;
      count++;
    } else {
      for (int i2 = 0; i2*2 <= total; i2++) {
	if ( i1 + 2*i2 == total ) {
	  cout << i1 << "x1p + " << i2 << "x2p = " << total << endl;
	  count++;
	} else {
	  for (int i5 = 0; i5*5 <= total; i5++) {
	    if ( i1 + 2*i2 + 5*i5 == total ) {
	      cout << i1 << "x1p + " << i2 << "x2p + " << i5 << "x5p = " << total << endl;
	      count++;
	    } else {
	      for (int i10 = 0; i10*10 <= total; i10++) {
		if ( i1 + 2*i2 + 5*i5 + 10*i10 == total ) {
		  cout << i1 << "x1p + " << i2 << "x2p + " << i5 << "x5p + " << i10 << "x10p = " << total << endl;
		  count++;
		} else {
		  for (int i20 = 0; i20*20 <= total; i20++) {
		    if ( i1 + 2*i2 + 5*i5 + 10*i10 + 20*i20 == total ) {
		      cout << i1 << "x1p + " << i2 << "x2p + " << i5 << "x5p + " << i10 << "x10p + " << i20 << "x20p = " << total << endl;
		      count++;
		    } else {
		      for (int i50 = 0; i50*50 <= total; i50++) {
			if ( i1 + 2*i2 + 5*i5 + 10*i10 + 20*i20 + 50*i50 == total ) {
			  cout << i1 << "x1p + " << i2 << "x2p + " << i5 << "x5p + " << i10 << "x10p + " << i20 << "x20p + " << i50 << "x50p = " << total << endl;
			  count++;
			} else {
			  for (int i100 = 0; i100*100 <= total; i100++) {
			    if ( i1 + 2*i2 + 5*i5 + 10*i10 + 20*i20 + 50*i50 + 100*i100 == total ) {
			      cout << i1 << "x1p + " << i2 << "x2p + " << i5 << "x5p + " << i10 << "x10p + " << i20 << "x20p + " << i50 << "x50p + " << i100 << "x£1 = " << total << endl;
			      count++;
			    } else {
			      for (int i200 = 0; i200*200 <= total; i200++) {
				if ( i1 + 2*i2 + 5*i5 + 10*i10 + 20*i20 + 50*i50 + 100*i100 + 200*i200 == total ) {
				  cout << i1 << "x1p + " << i2 << "x2p + " << i5 << "x5p + " << i10 << "x10p + " << i20 << "x20p + " << i50 << "x50p + " << i100 << "x£1 + " << i200 << "x£2 = " << total << endl;
				  count++;
				}
			      }
			    }
			  }
			}
		      }
		    }
		  }
		}
	      }
	    }
	  }
	}
      }
    }
  }
  return count;
}

int main(int argc, char* argv[])
{
  int total = 200;
  if ( argc > 1 ) {
    total = atoi(argv[1]);
  }

  int count = coin_count(total);
  cout << "there are " << count << " ways to make " << total << endl;
}
