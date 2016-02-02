for ((year=1901;year<2001;year++)); do cal $year | cut -c1,2,23-25,46-49 | grep " 1[^0-9]"; done | while read x y z; do echo $x; echo $y; echo $z; done | grep -c 1
