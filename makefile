CXX = clang++
CXXFLAGS = -std=c++23 -Wall -Wfatal-errors
SOURCES := $(wildcard ./utils/*.cpp ./day*/*.cpp ./*.cpp)

run: clean debug
	clear
	./target/aoc2024

profileable:
	$(CXX) $(CXXFLAGS) -pg $(SOURCES) -o ./target/aoc2024

debug:
	$(CXX) $(CXXFLAGS) -g $(SOURCES) -o ./target/aoc2024

opt2mold:
	$(CXX) $(CXXFLAGS) -fuse-ld=mold -O2 $(SOURCES) -o ./target/opt2mold

opt3mold:
	$(CXX) $(CXXFLAGS) -fuse-ld=mold -O3 $(SOURCES) -o ./target/opt3mold

optzmarch:
	$(CXX) $(CXXFLAGS) -Oz -march=native $(SOURCES) -o ./target/optzmarch

optsmarch:
	$(CXX) $(CXXFLAGS) -Os -march=native $(SOURCES) -o ./target/optsmarch

opt1march:
	$(CXX) $(CXXFLAGS) -O1 -march=native $(SOURCES) -o ./target/opt1march

opt2march:
	$(CXX) $(CXXFLAGS) -O2 -march=native $(SOURCES) -o ./target/opt2march

opt3march:
	$(CXX) $(CXXFLAGS) -O3 -march=native $(SOURCES) -o ./target/opt3march

opt2mm:
	$(CXX) $(CXXFLAGS) -fuse-ld=mold -O2 -march=native $(SOURCES) -o ./target/opt2moldmarch

opt3mm:
	$(CXX) $(CXXFLAGS) -fuse-ld=mold -O3 -march=native $(SOURCES) -o ./target/opt3moldmarch

optz:
	$(CXX) $(CXXFLAGS) -Oz $(SOURCES) -o ./target/optz

opts:
	$(CXX) $(CXXFLAGS) -Os $(SOURCES) -o ./target/opts

opt1:
	$(CXX) $(CXXFLAGS) -O1 $(SOURCES) -o ./target/opt1

opt2:
	$(CXX) $(CXXFLAGS) -O2 $(SOURCES) -o ./target/opt2

opt3:
	$(CXX) $(CXXFLAGS) -O3 $(SOURCES) -o ./target/opt3

pgo:
	$(CXX) $(CXXFLAGS) -fuse-ld=mold -O3 -march=native -fprofile-generate $(SOURCES) -o ./target/pgo_generator
	(rm -rf ./tmp || true)
	mkdir -p ./tmp
	LLVM_PROFILE_FILE="./tmp/code-all.profraw" ./target/pgo_generator > /dev/null
	LLVM_PROFILE_FILE="./tmp/code-j14.profraw" ./target/pgo_generator 14 > /dev/null
	LLVM_PROFILE_FILE="./tmp/code-j9.profraw" ./target/pgo_generator 9 > /dev/null
	LLVM_PROFILE_FILE="./tmp/code-6to1.profraw" ./target/pgo_generator 6 1 > /dev/null
	LLVM_PROFILE_FILE="./tmp/code-j6.profraw" ./target/pgo_generator 6 > /dev/null
	LLVM_PROFILE_FILE="./tmp/code-all-pt2.profraw" ./target/pgo_generator > /dev/null
	LLVM_PROFILE_FILE="./tmp/code-all-pt3.profraw" ./target/pgo_generator 1 14 > /dev/null
	llvm-profdata merge -output=./tmp/code.profdata ./tmp/code-*.profraw
	$(CXX) $(CXXFLAGS) -fuse-ld=mold -O3 -march=native -fprofile-use=./tmp/code.profdata $(SOURCES) -o ./target/pgo
	rm -f ./target/pgo_generator
	rm -rf ./tmp

clean:
	rm -rf ./target
	mkdir -p ./target

vs: clean
	$(CXX) $(CXXFLAGS) $(SOURCES) -o ./target/conrad_attempt_no_opt
	$(CXX) $(CXXFLAGS) -O3 -march=native $(SOURCES) -o ./target/conrad_attempt_opt3_march

all: clean debug optz opts opt1 opt2 opt3 optzmarch optsmarch opt1march opt2march opt3march opt2mold opt3mold opt2mm opt3mm pgo