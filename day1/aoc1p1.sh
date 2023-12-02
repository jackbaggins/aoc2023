#!/bin/bash
# Advent of Code Day 1 Part 2

# First parameter of script is input file.
if [ $# -eq 0 ]; then
    echo "First parameter is input file 'sh aoc1p2.sh <inputfile>'"
    exit 1  # Exit the script with an error status
fi


awk '{
    first = ""; last = ""; 
    for (i=1; i<=length($0); i++) {
        c = substr($0, i, 1);
        if (c ~ /[0-9]/) {
            if (first == "") first = c; 
            last = c;
        }
    }
    if (first != "" && last != "") print first last;
}' $1 | awk '{ sum += $1 } END { print "Total:",sum }'
