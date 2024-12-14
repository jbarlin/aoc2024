#!/bin/bash
set -ev

mkdir -p ./clone

pushd ./clone

git clone git@github.com:dorgek/aoc2024.git .

rm -f ./Makefile
cp ../Makefile ./Makefile
cp ../main.cpp ./main.cpp

make vs

popd

mv ./clone/target/dorgek_attempt_no_opt ../../target/dorgek_attempt_no_opt
mv ./clone/target/dorgek_attempt_opt3_march ../../target/dorgek_attempt_opt3_march

rm -rf ./clone