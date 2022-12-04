#!/usr/bin/sh
# Usage: ~/stress.sh -sm smart -st stupid -g gen
smrt = "smart"
stpid = "stupid"
gn = "gen" 

while getopts sm:st:g: opt
do
    case "${opt}" in
        sm) smrt="${OPTARG}";;
        st) stpid="${OPTARG}";;
        g) gn="${OPTARG}";;
    esac
done
g++ -std=c++20 -O2 "${smrt}.cpp" -o ${smrt} 
g++ -std=c++20 -O2 "${stpid}.cpp" -o ${stpid} 
g++ -std=c++20 -O2 "${gn}.cpp" -o ${gn} 
for((i=1;i<1000;++i)); do
    echo $i;
    ./${gn} $i > genIn;
    diff <(./${smrt} < genIn) <(./${stpid} < genIn) || break;
done
#~/stress.sh -sm smart -st stupid -g gen