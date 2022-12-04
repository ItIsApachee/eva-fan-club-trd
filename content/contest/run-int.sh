#!/usr/bin/bash
# Usage: ~/run-int.sh -n A

name="a"
while getopts n: opt
do
    case "${opt}" in
        n) name="${OPTARG}";;
    esac
done
ulimit -s 600000
g++ -std=c++20 -fno-stack-limit -O2 "${name}.cpp" -o ${name} 
time ${name}
echo $tim