CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -O2 -Wno-parentheses

all: test

test: test.cpp BST.h
	$(CXX) $(CXXFLAGS) -o test test.cpp

clean:
	rm -f test *.o
