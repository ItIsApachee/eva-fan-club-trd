#!/usr/bin/bash
# Usage: ~/run.sh -n A -i input -o output

inn="input"
out="output"
name="a"
while getopts n:i:o: opt
do
    case "${opt}" in
        n) name="${OPTARG}";;
        i) inn="${OPTARG}";;
        o) out="${OPTARG}";;
    esac
done
echo $inn
echo $out
echo $name
ulimit -s 600000
g++ -std=c++20 -fno-stack-limit -O2 "${name}.cpp" -o ${name} 
time ${name} < ${inn} > ${out}
echo $tim