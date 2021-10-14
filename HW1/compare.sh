#!/bin/bash

#some variable
iteration=5
start=10
end=1000
multiplier=10
array_size=0
p_start=1
p_end=100
# argument parser
while getopts "s:e:m:" opt
do
  case $opt in
    s) start=$OPTARG ;;
    e) end=$OPTARG ;;
    m) multiplier=$OPTARG ;;
  esac
done

# compile files first
make all

# create and clear statistic files
> main-base-result.txt
> main-fork-result.txt
> main-thread-result.txt
> main-thread-mutex-result.txt

## process-num-comparison
#array_size=100000
#for (( i=${p_start}; i<=${p_end}; i+=1 )); do
#
#    echo "array size: 10000000, max num: 100"
#    ./main-base -s ${array_size} -m 100000 -i 5 -h >> main-base-result.txt
#    echo "running fork..."
#    ./main-fork -s ${array_size} -m 100000 -n ${i} -i 5 -h >> main-fork-result.txt
#    echo "running mutex..."
#    ./main-thread-mutex -s ${array_size} -m 100000 -n ${i} -i 5 -h >> main-thread-mutex-result.txt
#done

# data-size-comparison
process_num=16
for (( i=${start}; i<=${end}; i=${i}*${multiplier} )); do
    array_size=$(( ${i} * 1000 ))
    echo "array size: ${array_size}, max num: ${i}"
    ./main-base -s ${array_size} -m ${i} -i 5 -h >> main-base-result.txt
    echo "running fork..."
    ./main-fork -s ${array_size} -m ${i} -n 6 -i 5 -h >> main-fork-result.txt
    echo "running mutex..."
    ./main-thread-mutex -s ${array_size} -m ${i} -n 6 -i 5 -h >> main-thread-mutex-result.txt
done

# run evaluations
#for (( i=${start}; i<=${end}; i=${i}*${multiplier} )); do
#    array_size=$(( ${i} * 1000 ))
#    echo "array size: ${array_size}, max num: ${i}"
#    for (( k=${p_start}; k<=${p_end}; k+=1 )); do
#        echo "running fork..."
#        ./main-fork -s ${array_size} -m ${i} -n ${k} -i 5 -h >> main-fork-result.txt
#        echo "running mutex..."
#        ./main-thread-mutex -s ${array_size} -m ${i} -i 5 -n ${k} -h >> main-thread-mutex-result.txt
#    done
#done


## mutex comparison
#array_size=1000000
#for (( i=${p_start}; i<=${p_end}; i+=1 )); do
#    echo "running thread-mutex..."
#    ./main-thread-mutex -s ${array_size} -m 2 -n ${i} -i 5 -h >> main-thread-mutex-result.txt
#    echo "running thread"
#     ./main-thread -s ${array_size} -m 2 -n ${i} -i 5 -h >> main-thread-result.txt
#done