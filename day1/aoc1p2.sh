#!/bin/bash
# Advent of Code Day 1 Part 2

# First parameter of script is input file.
if [ $# -eq 0 ]; then
    echo "First parameter is input file 'sh aoc1p2.sh <inputfile>'"
    exit 1  # Exit the script with an error status
fi


awk '
BEGIN {
    replace["one"] = "1";
    replace["two"] = "2";
    replace["three"] = "3";
    replace["four"] = "4";
    replace["five"] = "5";
    replace["six"] = "6";
    replace["seven"] = "7";
    replace["eight"] = "8";
    replace["nine"] = "9";
}

{
    line = $0;
    result = ""; 
    i = 1; # Init position

    while (i <= length(line)) {
        found = 0;
        for (word in replace) {
            wordLen = length(word);
            if (substr(line, i, wordLen) == word) {
                # Do replace if match at position
                result = result replace[word];
                # Step the pos pointer back one, for overlaps
                i += wordLen - 1; 
                found = 1;
                break;
            }
        }
        if (!found) {
            # No match, step pointer
            result = result substr(line, i, 1);
            i++;
        }
    }

    print result;
}' $1 | awk '{
    first = ""; last = ""; 
    for (i=1; i<=length($0); i++) {
        c = substr($0, i, 1);
        if (c ~ /[0-9]/) {
            if (first == "") first = c; 
            last = c;
        }
    }
    if (first != "" && last != "") print first last;
}' | awk '{ sum += $1 } END { print "Total:",sum }'