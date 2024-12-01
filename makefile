CXX = clang++
CXXFLAGS = -std=c++23 -Wall
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cpp=.o)

run01: day01
	./target/dists/day01

day01: day01.o
	mkdir -p ./target/dists
	$(CXX) $(CXXFLAGS) ./target/objs/day01.o -o ./target/dists/day01

day01.o: clean
	mkdir -p ./target/objs/
	$(CXX) $(CXXFLAGS) -c ./day01/main.cpp -o ./target/objs/day01.o

clean:
	rm -rf ./target