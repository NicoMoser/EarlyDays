#!/bin/sh

# just a guess at an upper limit: 100000

for ((i=1;i<100000;i++)); do echo $(( ${i}*(${i}+1)/2 )) ; done > triagonal.txt
for ((i=1;i<100000;i++)); do echo $(( ${i}*(2*${i}-1) )) ; done > hexagonal.txt
for ((i=1;i<100000;i++)); do echo $(( ${i}*(3*${i}-1)/2 )) ; done > pentagonal.txt

# find matches between the two sparser files
cat hexagonal.txt pentagonal.txt | sort | uniq -d

# 1
# 1533776805
# 40755

# find the unknown entry in triagonal.txt
grep 1533776805 triagonal.txt 
# (yes, it's there)

