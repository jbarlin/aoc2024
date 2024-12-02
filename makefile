CXX = clang++
CXXFLAGS = -std=c++23 -Wall
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cpp=.o)

run02: day02
	./target/dists/day02

day02: day02.o
	mkdir -p ./target/dists
	$(CXX) $(CXXFLAGS) ./target/objs/day02.o -o ./target/dists/day02

day02.o: clean
	mkdir -p ./target/objs/
	$(CXX) $(CXXFLAGS) -c ./day02/main.cpp -o ./target/objs/day02.o

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