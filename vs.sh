#!/bin/bash
set -e

NUM_DAYS=13
NUM_DAYS_JUST_THROX_STOP=6
NUM_DAYS_DORGEK_START=5
NUM_DAYS_DORGEK_ADDIT="08"

make vs

clear

pushd ./vs/dorgek

bash ./setup.sh

popd

clear

pushd ./vs/throx

bash ./setup.sh

popd

clear

# First do all days

hyperfine --export-markdown ./tmp/bench.md \
  -L upto ${NUM_DAYS} \
  './target/conrad_attempt_no_opt 1 {upto}' \
  './target/throx_attempt_no_opt 1 {upto}'

echo -e "# Advent of Code 2024 vs others\n\nAll builds are done with gcc, and get the same puzzle inputs just to keep things even.\n\nResults collected using hyperfine, and include the following process for each day:\n 1. Reading in the test input\n 2. Running the test input\n 3. Reading in the puzzle input\n 4. Solving the puzzle\n\n## All days combined" >./results_compete.md

echo -e "\n###No optimisations\n" >> ./results_compete.md

cat ./tmp/bench.md >>./results_compete.md

hyperfine --export-markdown ./tmp/bench.md \
  -L upto ${NUM_DAYS} \
  './target/conrad_attempt_opt3_march 1 {upto}' \
  './target/throx_attempt_opt3_march 1 {upto}'

echo -e "\n###-O3 -march=native\n" >> ./results_compete.md

cat ./tmp/bench.md >>./results_compete.md

# Do up to day 5 since dorgek's day 6 & 7 takes 900 seconds :/

echo -e "\n## Up to day 5\n" >>./results_compete.md

echo -e "\n###No optimisations\n" >> ./results_compete.md

hyperfine --export-markdown ./tmp/bench.md \
  -L upto 5 \
  './target/conrad_attempt_no_opt 1 {upto}' \
  './target/dorgek_attempt_no_opt 1 {upto}' \
  './target/throx_attempt_no_opt 1 {upto}'

cat ./tmp/bench.md >>./results_compete.md

echo -e "\n###-O3 -march=native\n" >> ./results_compete.md

hyperfine --export-markdown ./tmp/bench.md \
  -L upto 5 \
  './target/dorgek_attempt_opt3_march 1 {upto}' \
  './target/throx_attempt_opt3_march 1 {upto}' \
  './target/conrad_attempt_opt3_march 1 {upto}'

cat ./tmp/bench.md >>./results_compete.md

# Day by day

for i in $(seq -f "%02g" $NUM_DAYS -1 $NUM_DAYS_JUST_THROX_STOP); do

  echo -e "\n## Day ${i}\n" >>./results_compete.md
  echo -e "\n###No optimisations\n" >> ./results_compete.md

  if [[ "$NUM_DAYS_DORGEK_ADDIT" == "${i}" ]]; then

    hyperfine --export-markdown ./tmp/bench.md \
      -L day ${i} \
      './target/conrad_attempt_no_opt {day}' \
      './target/throx_attempt_no_opt {day}' \
      './target/dorgek_attempt_no_opt {day}'

  else

    hyperfine --export-markdown ./tmp/bench.md \
      -L day ${i} \
      './target/conrad_attempt_no_opt {day}' \
      './target/throx_attempt_no_opt {day}'

  fi

  cat ./tmp/bench.md >>./results_compete.md

  echo -e "\n###-O3 -march=native\n" >> ./results_compete.md

  if [[ "$NUM_DAYS_DORGEK_ADDIT" == "${i}" ]]; then

    hyperfine --export-markdown ./tmp/bench.md \
      -L day ${i} \
      './target/throx_attempt_opt3_march {day}' \
      './target/dorgek_attempt_opt3_march {day}' \
      './target/conrad_attempt_opt3_march {day}'

  else

    hyperfine --export-markdown ./tmp/bench.md \
      -L day ${i} \
      './target/throx_attempt_opt3_march {day}' \
      './target/conrad_attempt_opt3_march {day}'
  fi

  

  cat ./tmp/bench.md >>./results_compete.md

done

for i in $(seq -f "%02g" $NUM_DAYS_DORGEK_START -1 1); do

  echo -e "\n## Day ${i}\n" >>./results_compete.md
  echo -e "\n###No optimisations\n" >> ./results_compete.md

  hyperfine --export-markdown ./tmp/bench.md \
    -L day ${i} \
    './target/conrad_attempt_no_opt {day}' \
    './target/throx_attempt_no_opt {day}' \
    './target/dorgek_attempt_no_opt {day}'

  cat ./tmp/bench.md >>./results_compete.md

  echo -e "\n###-O3 -march=native\n" >> ./results_compete.md

  hyperfine --export-markdown ./tmp/bench.md \
    -L day ${i} \
    './target/dorgek_attempt_opt3_march {day}' \
    './target/throx_attempt_opt3_march {day}' \
    './target/conrad_attempt_opt3_march {day}'

  cat ./tmp/bench.md >>./results_compete.md

done