CXX = g++
CXXFLAGS = -std=c++23 -fext-numeric-literals
SOURCES := $(wildcard ./day*/*.cpp ./main.cpp)

vs:
	rm -rf ./target
	mkdir -p ./target
	$(CXX) $(CXXFLAGS) $(SOURCES) -o ./target/throx_attempt_no_opt
	$(CXX) $(CXXFLAGS) -O3 -march=native $(SOURCES) -o ./target/throx_attempt_opt3_march
