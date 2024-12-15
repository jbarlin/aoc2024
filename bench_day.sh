#!/bin/bash
set -e

NUM_DAYS=14
NUM_DAYS_MIN_2=1

#make all

#clear

(rm -rf tmp) || true

mkdir -p tmp

# First do all days

hyperfine --export-markdown ./tmp/bench.md \
    --warmup 5 \
    './target/aoc2024' \
    './target/optz' \
    './target/opts' \
    './target/opt1' \
    './target/opt2' \
    './target/opt3' \
    './target/optzmarch' \
    './target/optsmarch' \
    './target/opt1march' \
    './target/opt2march' \
    './target/opt3march' \
    './target/opt2mold' \
    './target/opt3mold' \
    './target/opt2moldmarch' \
    './target/opt3moldmarch' \
    './target/pgo'

echo -e "# Advent of Code 2024 benchmarkings\n\nResults collected using hyperfine, and include the following process for each day:\n 1. Reading in the test input\n 2. Validating the test input gives the correct answers\n 3. Reading in the puzzle input\n 4. Solving the puzzle\n\n## All days combined\n" >./results_benchmark.md

cat ./tmp/bench.md >>./results_benchmark.md

for i in $(seq -f "%02g" $NUM_DAYS -1 $NUM_DAYS_MIN_2)
do
  
  echo -e "\n## Day ${i}\n" >> ./results_benchmark.md
  hyperfine --export-markdown ./tmp/bench.md \
    --warmup 5 \
    -L day ${i} \
    './target/aoc2024 {day}' \
    './target/optz {day}' \
    './target/opts {day}' \
    './target/opt1 {day}' \
    './target/opt2 {day}' \
    './target/opt3 {day}' \
    './target/optzmarch {day}' \
    './target/optsmarch {day}' \
    './target/opt1march {day}' \
    './target/opt2march {day}' \
    './target/opt3march {day}' \
    './target/opt2mold {day}' \
    './target/opt3mold {day}' \
    './target/opt2moldmarch {day}' \
    './target/opt3moldmarch {day}' \
    './target/pgo {day}'

    cat ./tmp/bench.md >>./results_benchmark.md

done

