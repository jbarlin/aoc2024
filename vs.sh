#!/bin/bash
set -e

NUM_DAYS=8

make vs

clear

pushd ./vs/dorgek

bash ./setup.sh

popd

clear

# First do all days

hyperfine --export-markdown ./tmp/bench.md \
  --warmup 5 \
  './target/dorgek_attempt_no_opt' \
  './target/conrad_attempt_no_opt'

echo -e "# Advent of Code 2024 vs others\n\nAll builds are done with gcc, and get the same puzzle inputs just to keep things even.\n\nResults collected using hyperfine, and include the following process for each day:\n 1. Reading in the test input\n 2. Running the test input\n 3. Reading in the puzzle input\n 4. Solving the puzzle\n\n## All days combined" >./results_compete.md

echo -e "\n###No optimisations\n" >> ./results_compete.md

cat ./tmp/bench.md >>./results_compete.md

hyperfine --export-markdown ./tmp/bench.md \
  --warmup 5 \
  './target/dorgek_attempt_opt2_march' \
  './target/conrad_attempt_opt2_march'

echo -e "\n###-O2 -march=native\n" >> ./results_compete.md

cat ./tmp/bench.md >>./results_compete.md

for i in $(seq -f "%02g" $NUM_DAYS -1 1); do

  echo -e "\n## Day ${i}\n" >>./results_compete.md
  echo -e "\n###No optimisations\n" >> ./results_compete.md

  hyperfine --export-markdown ./tmp/bench.md \
    --warmup 5 \
    -L day ${i} \
    './target/dorgek_attempt_no_opt {day}' \
    './target/conrad_attempt_no_opt {day}'

  cat ./tmp/bench.md >>./results_compete.md

  echo -e "\n###-O2 -march=native\n" >> ./results_compete.md

  hyperfine --export-markdown ./tmp/bench.md \
    --warmup 5 \
    -L day ${i} \
    './target/dorgek_attempt_opt2_march {day}' \
    './target/conrad_attempt_opt2_march {day}'

  cat ./tmp/bench.md >>./results_compete.md

done

mv ./results_compete.md ./competing_up_to_day_8.md