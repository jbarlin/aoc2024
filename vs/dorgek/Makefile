CXX 	  := g++
CXXFLAGS := -Wall -Wextra -std=c++20
SOURCES   := $(wildcard src/**/*.cpp ./main.cpp)

vs: clean
	$(CXX) $(CXXFLAGS) $(SOURCES) -o ./target/dorgek_attempt_no_opt
	$(CXX) $(CXXFLAGS) -O3 -march=native $(SOURCES) -o ./target/dorgek_attempt_opt3_march

clean:
	rm -rf ./target
	mkdir -p ./target