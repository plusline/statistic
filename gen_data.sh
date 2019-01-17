#!/bin/bash
#set -x 

i=1
while [ $i -le 12000 ]
do
	echo $i
	perf stat -B -e L1-dcache-loads,L1-dcache-load-misses -r 1 -o perf_256.txt ./test_256 $i
	perf stat -B -e L1-dcache-loads,L1-dcache-load-misses -r 1 -o perf_65536.txt ./test_65536 $i
	echo $i | tr '\n' '\t' >> perf_data.txt
	cat perf_256.txt | grep -oP "#[ 0-9]*[.][0-9]*" | grep -oP "[0-9.]*" | tr '\n' '\t' >> perf_data.txt
	cat perf_65536.txt | grep -oP "#[ 0-9]*[.][0-9]*" | grep -oP "[0-9.]*" | tr '\n' '\t' >> perf_data.txt
	echo "">>perf_data.txt
	i=$((i+1))
done
