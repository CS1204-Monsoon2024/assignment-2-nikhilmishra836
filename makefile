# Makefile for compiling main.cpp

# Target to create the executable
main: Hashtable.cpp
	g++ -Wall ./HashTable.cpp -o HashTable.out

# Clean up generated files
clean:
	rm -f ./HashTable.out
