#!/bin/bash
set -ev

mkdir -p ./clone

pushd ./clone

git clone git@github.com:throx/advent2024.git .
git apply ../split_headers.patch

cp ../Makefile ./Makefile
cp ../main.cpp ./main.cpp

echo -e "\ntarget/*" >> ./.gitignore

find d*/*.cpp -type f -exec sed -i 's/#include <conio.h>/#include <cstring>/g' {} \;

find d*/*.cpp -type f -exec sed -i 's/using namespace std;/using namespace std; typedef long long __int64; typedef long __int32;/g' {} \;

find d* -type d -print0 | while IFS= read -r -d $'\0' dir; do
  folder_name=$(basename "$dir")
  find "$dir" -name "*.cpp" -print0 | while IFS= read -r -d $'\0' file; do
    sed -i -e "s/int main()/namespace ${folder_name}{using namespace std; int main()/" -e '$a}' "$file"
    sed -i "1 i #include \"./main.h\"" "$file"
    echo -e "#pragma once\nnamespace ${folder_name}\n{\n\tint main();}" > "${folder_name}/main.h"
  done
done

find d*/*.cpp -type f -exec sed -i 's/_getch();/return 0;/g' {} \;

sed -i "7 i typedef long long __int64;" ./shared/Point.h
sed -i "s#at\[i\]#at(i)#g" ./shared/Point.h

sed -i "9 i typedef long long __int64;" ./shared/Split.h

sed -i "4 i #include <cmath>" ./day7/day7.cpp

sed -i "4 i #include <climits>" ./day9/day9.cpp

sed -i "s/0i64/(long long) 0/g" ./day11/day11.cpp
sed -i "4 i #include <cmath>" ./day11/day11.cpp

sed -i "s/10000000000000i64/(long long) 10000000000000/g" ./day13/day13.cpp


make vs

popd

mv ./clone/target/throx_attempt_no_opt ../../target/throx_attempt_no_opt
mv ./clone/target/throx_attempt_opt3_march ../../target/throx_attempt_opt3_march

rm -rf ./clone