# Advent of Code 2023

Solutions for Advent of Code 2023. Each day in a folder.

## Day 1:
Chosen solution: **Bash Scripts**

Using `awk` exclusively. Successfully provides solution for both part one and two of the Day 1 challenge.
Each script takes a single parameter, which is the given input file as plain text. 

Example run Part 1: 'sh aoc1p1.sh <inputfile>'

Example run Part 2: 'sh aoc1p2.sh <inputfile>'

_Ran/developed on Raspbian bullseye on Pi400._

## Day 2:
Chosen solution: **C++**

Hamfisted approach with minimal C++ skillset. I would like to redo this with better error handling and
building out parts as separate functions. Right now it's a mess of while loops with if statements.

_but it works_

### Part 1:

Simple Build:
`g++ -o d2p1 d2p1_main.cpp`

Run With:
`./d2p1 <inputfile> -R <red_int> -G <green_int> -B <blue_int>`

### Part 2:

Able to reuse a large portion of the program for part 1. Removed a chunk of unneeded functionaltiy - and added in the multiplication and summation parts.

Simple Build:
`g++ -o d2p2 d2p2_main.cpp`

Run With:
`./d2p2 <inputfile>`

_Ran/developed on Raspbian bullseye on Pi400._

## Day 3:
Chosen solution: **C++**

### Part 1:

This is probably the messiest thing anyone has ever seen. Essentially - create and array of strings, and while/if/for iterations through each row, column, and individual character to eventually get the solution. May or may not be able to re-use any of this for part 2...

Simple Build:
`g++ -o d2p2 d3p1_main.cpp`

Run With:
`./d3p1 <inputfile>`

### Part 2:

Used the bulk of part 1 for this. Changed the way the number check and accumulation was working. Added some additional functions for dealing with arrays. Login on this one was to find all of the coordinates of the stars, and then list the number the star was touching. 

Once the coordinates and touching numbers have been identified - pass the vector to a function that will find coordinate matches (multiple numbers touching the same star at [row][column]) - and multiply them - summing the products of each.

Simple Build:
`g++ -o d3p2 d3p2_main.cpp`

Run With:
`/d3p2 <inputfile>`