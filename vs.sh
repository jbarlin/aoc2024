#!/bin/bash
set -e

NUM_DAYS=7

make debug

clear

(rm -rf tmp) || true

mkdir -p tmp

pushd ../dorgek_aoc2024

git reset --hard
git pull

mkdir -p ./bin

# OK, now create a new "main" that is compatible with mine
#   we will have it read the same inputs as I do, just to make it fair
#   NOTE: I need to adjust day 3 to read from a file
echo -e "#include \"./util/util.h\"\n#include <iostream>\n#include <cassert>" >./src/main.cpp
for i in $(seq -f "%02g" $NUM_DAYS -1 1); do
  echo -e "#include \"./aoc/day${i}.h\"\n" >>./src/main.cpp
done
for i in $(seq -f "%02g" $NUM_DAYS -1 1); do
  tee -a ./src/main.cpp <<EOT

int d${i}() {
  // Do the tests, then the real ones
  day${i}::partOne("day${i}/test_input.txt");
  day${i}::partTwo("day${i}/test_input.txt");
  day${i}::partOne("day${i}/puzzle_input.txt");
  day${i}::partTwo("day${i}/puzzle_input.txt");
  return 0;
}

EOT
done

echo -e "int allDays() {\n" >>./src/main.cpp

for i in $(seq -f "%02g" $NUM_DAYS -1 1); do
  echo -e "d${i}();\n" >>./src/main.cpp
done

echo -e "return 0;\n}\n" >>./src/main.cpp

tee -a ./src/main.cpp <<EOT
int main(int argc, char *argv[])
{
  if (argc == 2)
    {
      int day = std::stoi(argv[1]);
      switch (day)
        {
EOT

for i in $(seq -f "%02g" $NUM_DAYS -1 1); do
  tee -a ./src/main.cpp <<EOT
case std::stoi("${i}"):
  std::cout << "Day ${i}" << std::endl;
  return d${i}();
  break;
EOT
done

tee -a ./src/main.cpp <<EOT
default:
            return allDays();
            break;
        }
    }
    else
    {
        return allDays();
    }

    return 0;
}
EOT

clear
rm -rf ./bin
mkdir -p ./bin
make all

popd

mv ./target/aoc2024 ./target/jbarlin_attempt
mv ../dorgek_aoc2024/bin/main ./target/dorgek_attempt

clear

# First do all days

hyperfine --export-markdown ./tmp/bench.md \
  --warmup 5 \
  './target/jbarlin_attempt' \
  './target/dorgek_attempt'

echo -e "# Advent of Code 2024 vs others\n\nAll builds are debug builds with gcc, and get the same puzzle inputs just to keep things even.\n\n## All days combined\n" >./results_compete.md

cat ./tmp/bench.md >>./results_compete.md

for i in $(seq -f "%02g" $NUM_DAYS -1 1); do

  echo -e "\n## Day ${i}\n" >>./results_compete.md
  hyperfine --export-markdown ./tmp/bench.md \
    --warmup 5 \
    -L day ${i} \
    './target/jbarlin_attempt {day}' \
    './target/dorgek_attempt {day}'

  cat ./tmp/bench.md >>./results_compete.md

done
