# Makefile for compiling main.cpp

# Target to create the executable
main: main.cpp
	g++ -Wall main.cpp -o main.out

# Clean up generated files
clean:
	rm -f main.out
