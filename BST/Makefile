# Makefile

# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
TEX = pdflatex
TEXFLAGS = -interaction=nonstopmode
SRC = main.cpp
OBJ = main.o
REPORT = report.tex

# Targets
.PHONY: all run report clean

# Default target
all: run

# Build and run the program
run: $(OBJ)
	$(CXX) $(OBJ) -o bst_test
	./bst_test

# Compile the report
report:
	xelatex report.tex
# Clean up
clean:
	rm -f $(OBJ) bst_test report.pdf *.log *.aux
