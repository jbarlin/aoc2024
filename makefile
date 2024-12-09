CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wfatal-errors
SOURCES := $(wildcard ./day*/*.cpp ./*.cpp)

run: clean debug
	clear
	./target/aoc2024

profileable:
	mkdir -p ./target
	$(CXX) $(CXXFLAGS) -pg $(SOURCES) -o ./target/aoc2024

debug:
	mkdir -p ./target
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

clean:
	rm -rf ./target

all: clean debug optz opts opt1 opt2 opt3 optzmarch optsmarch opt1march opt2march opt3march opt2mold opt3mold opt2mm opt3mm