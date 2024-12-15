#!/bin/bash
set -ev

if [ ! -e ./clone ]; then
  git clone git@github.com:throx/advent2024.git ./clone
fi

pushd ./clone
git reset --hard
git clean -fdx
git pull

cp ../Makefile ./Makefile
cp ../main.cpp ./main.cpp

echo -e "\ntarget/*" >> ./.gitignore

find d* -type d -print0 | while IFS= read -r -d $'\0' dir; do
  folder_name=$(basename "$dir")
  find "$dir" -name "*.cpp" -print0 | while IFS= read -r -d $'\0' file; do
    sed -i -e "s/int main()/namespace ${folder_name}{using namespace std; int main()/" -e '$a}' "$file"
    sed -i "1 i #include \"./main.h\"" "$file"
    echo -e "#pragma once\nnamespace ${folder_name}\n{\n\tint main();}" > "${folder_name}/main.h"
  done
done


make vs

popd

mv ./clone/target/throx_attempt_no_opt ../../target/throx_attempt_no_opt
mv ./clone/target/throx_attempt_opt3_march ../../target/throx_attempt_opt3_march
