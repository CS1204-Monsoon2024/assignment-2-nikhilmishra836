#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Prime number checking function
bool isPrime(int num) {
    if (num < 2) return false;
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;
    for (int i = 5; i * i <= num; i += 6) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;
}

// Function to find the next prime number greater than a given number
int nextPrimefinder(int num) {
    while (!isPrime(num)) {
        num++;
    }
    return num;
}

class HashTable {
private:
    vector<int> table; // stores elements in the hash table
    int m; // size of the table
    int elements_num; // current number of elements in the table
    const double upperloadfactor = 0.8; // threshold for resizing

    // Hash function: key mod table size
    int hashfunction(int key) {
        return key % m;
    }

    // Resize the hash table when load factor exceeds threshold
    void resizingtable() {
        int oldsize = m; // current size of table
        m = nextPrimefinder(2 * oldsize); // find next prime number larger than double the current size
        vector<int> newtable(m, -1); // initialize new table with new size filled with -1
        for (int i = 0; i < oldsize; i++) {
            if (table[i] != -1 && table[i] != -2) { // if the current table position contains a valid element
                int newIndex = hashfunction(table[i]); // rehash element into new table
                int j = 0;
                while (newtable[newIndex] != -1) { // quadratic probing to find next empty spot
                    j++;
                    newIndex = (newIndex + j * j) % m;
                }
                newtable[newIndex] = table[i]; // place the rehashed element into the new table
            }
        }
        table = newtable; // replace old table with the resized table
    }

public:
    // Constructor: Initialize table with a prime size
    HashTable(int size) {
        m = isPrime(size) ? size : nextPrimefinder(size); // check if initial size is prime
        table.resize(m, -1); // initialize table with -1 (empty slots)
        elements_num = 0; // start with 0 elements
    }

    // Insert a key into the hash table
    void insert(int key) {
        // Check for duplicates
        int searchIndex = search(key);
        if (searchIndex != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        // Resize table if load factor exceeds threshold
        if ((double)elements_num / m > upperloadfactor) {
            resizingtable();
        }

        int index = hashfunction(key); // hash the key
        int i = 0;
        int newIndex = index;
        int firstTombstone = -1;

        // Use quadratic probing to resolve collisions
        while (table[newIndex] != -1) { // while not an empty spot
            if (table[newIndex] == -2 && firstTombstone == -1) {
                firstTombstone = newIndex; // mark the first tombstone found
            }
            i++;
            if (i * i >= m) { // if maximum probing limit reached
                cout << "Max probing limit reached!" << endl;
                return;
            }
            newIndex = (index + i * i) % m; // quadratic probing
        }

        if (firstTombstone != -1) {
            newIndex = firstTombstone; // reuse tombstone if found
        }

        table[newIndex] = key; // insert the key at the calculated position
        elements_num++; // increment element count
    }

    // Search for a key in the hash table
    int search(int key) {
        int index = hashfunction(key); // hash the key
        int i = 0;
        int newIndex = index;

        // Quadratic probing to find the element
        while (table[newIndex] != -1) { // continue searching until an empty slot is encountered
            if (table[newIndex] == key) { // if key is found
                return newIndex; // return the index
            }
            i++;
            newIndex = (index + i * i) % m; // quadratic probing
            if (i * i >= m) {
                break; // to prevent infinite probing
            }
        }
        return -1; // return -1 if key not found
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = search(key); // find the index of the key
        if (index != -1) {
            table[index] = -2; // mark slot as deleted using tombstone (-2)
            elements_num--; // decrement element count
        } else {
            cout << "Element not found" << endl; // if element is not found
        }
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < m; ++i) {
            if (table[i] == -1 || table[i] == -2) { // if slot is empty or deleted
                cout << "- ";
            } else {
                cout << table[i] << " "; // print the key at the position
            }
        }
        cout << endl;
    }
};

