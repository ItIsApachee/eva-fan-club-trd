#!/usr/bin/env bash
# usage:
# $ stress.sh <smart> <stupid> <gen> <number of tests>
g++ $1.cpp -o $1 -O2
g++ $2.cpp -o $2 -O2
g++ $3.cpp -o $3 -O2

for ((t=1;t<$4;t++))
do
    ./$3 $t > input
    ./$2 < input > slow.out
    ./$1 < input > smart.out

    diff smart.out slow.out || exit 123;
    echo "test $t passed"
done
echo Passed all \($4\) tests

