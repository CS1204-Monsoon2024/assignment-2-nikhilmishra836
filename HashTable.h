#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "HashTable.h"
#include <iostream>
#include <vector>

class HashTable {
public:
    HashTable(int size);
    void insert(int key);
    void remove(int key);
    bool search(int key);
    void printTable(); // Added this for printing the hash table

private:
    std::vector<int> table;  // The hash table will dynamically resize
    int m;  // The size of the table
    int elements_num;  // The number of elements currently in the table
    const double upperloadfactor = 0.8;  // Load factor threshold for resizing

    // Helper functions
    int hashfunction(int key);
    void resizingtable();
    bool isPrime(int num);
    int nextPrimefinder(int num);
};

#endif // HASHTABLE_H
