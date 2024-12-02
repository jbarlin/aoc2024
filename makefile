CXX = clang++
CXXFLAGS = -std=c++23 -Wall
SOURCES := $(wildcard ./**/*.cpp ./*.cpp)

run: clean all
	clear
	./target/aoc2024

all:
	mkdir -p ./target
	@echo "Building $(SOURCES)"
	$(CXX) $(CXXFLAGS) $(SOURCES) -o ./target/aoc2024

bench: clean all opt3 opt2 opts optz opt3march opt2march
	hyperfine --warmup 6 -N './target/aoc2024' './target/opt3' './target/opt2' './target/opt3m' './target/opt2m' './target/opts' './target/optz'

opt2march:
	$(CXX) $(CXXFLAGS) -O2 -march=native $(SOURCES) -o ./target/opt2m

opt3march:
	$(CXX) $(CXXFLAGS) -O3 -march=native $(SOURCES) -o ./target/opt3m

optz:
	$(CXX) $(CXXFLAGS) -Oz $(SOURCES) -o ./target/optz

opts:
	$(CXX) $(CXXFLAGS) -Os $(SOURCES) -o ./target/opts

opt2:
	$(CXX) $(CXXFLAGS) -O2 $(SOURCES) -o ./target/opt2

opt3:
	$(CXX) $(CXXFLAGS) -O3 $(SOURCES) -o ./target/opt3

clean:
	rm -rf ./target