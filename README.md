# aoc2023

Solutions for Advent of Code 2023. Each day in a folder.

## Day 1:
Chosen solution: Bash Scripts

Using `awk` exclusively. Successfully provides solution for both part one and two of the Day 1 challenge.
Each script takes a single parameter, which is the given input file as plain text. 

Example run Part 1: 'sh aoc1p1.sh <inputfile>'

Example run Part 2: 'sh aoc1p2.sh <inputfile>'

_Ran/developed on Raspbian bullseye on Pi400._

## Day 2:
Chosen solution: C++

Hamfisted approach with minimal C++ skillset. I would like to redo this with better error handling and
building out parts as separate functions. Right now it's a mess of while loops with if statements.

Dead simple build:
`g++ -o d2p1 d2p1_main.cpp`

Run with:
`./d2p1 <inputfile> -R <red_int> -G <green_int> -B <blue_int>`


