CXX = clang++
CXXFLAGS = -std=c++23 -Wall -Wfatal-errors -Wpedantic -Wextra -Wshadow -Wconversion
SOURCES := $(wildcard ./**/*.cpp ./*.cpp)

run: clean all
	clear
	./target/aoc2024

all:
	mkdir -p ./target
	@echo "Building $(SOURCES)"
	$(CXX) $(CXXFLAGS) $(SOURCES) -o ./target/aoc2024

bench: clean all optz opts opt1 opt2 opt3 optzmarch optsmarch opt1march opt2march opt3march
	clear
	hyperfine --warmup 6 -N './target/aoc2024' './target/optz' './target/opts' './target/opt1' './target/opt2' './target/opt3' './target/optzmarch' './target/optsmarch' './target/opt1march' './target/opt2march' './target/opt3march'

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

clean:
	rm -rf ./target