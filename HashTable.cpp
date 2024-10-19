#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;      // Hash table
    std::vector<bool> occupied;  // Tracks if a cell is occupied
    std::vector<bool> tombstone; // Tracks if a tombstone (deleted element) is present
    int size;                    // Current size of the table
    int currentSize;             // Number of actual elements in the table (excluding tombstones)
    double upperLoadFactor;      // Threshold for resizing

    // Helper function to check if a number is prime
    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Helper function to find the next prime greater than or equal to 'num'
    int nextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    // Hash function
    int hashFunction(int key) {
        return key % size;
    }

    // Function to resize the table
    void resize() {
        int oldSize = size;
        size = nextPrime(size * 2); // Resize to the next prime number
        std::vector<int> oldTable = table;
        std::vector<bool> oldOccupied = occupied;
        std::vector<bool> oldTombstone = tombstone;

        // Reinitialize new table
        table = std::vector<int>(size, -1);
        occupied = std::vector<bool>(size, false);
        tombstone = std::vector<bool>(size, false);
        currentSize = 0;

        // Rehash all elements from the old table to the new table
        for (int i = 0; i < oldSize; i++) {
            if (oldOccupied[i] && !oldTombstone[i]) {
                insert(oldTable[i]); // Insert valid elements into the new table
            }
        }
    }

public:
    // Constructor
    HashTable(int initialSize) : size(nextPrime(initialSize)), upperLoadFactor(0.7), currentSize(0) {
        table.resize(size, -1);
        occupied.resize(size, false);
        tombstone.resize(size, false);
    }

    // Insert function
    void insert(int key) {
        if ((double)currentSize / size >= upperLoadFactor) {
            resize(); // Resize if load factor exceeds the threshold
        }

        int index = hashFunction(key);
        int probing = 0; // Quadratic probing starts from 0

        while (occupied[index]) {
            if (table[index] == key && !tombstone[index]) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return; // Duplicate key found
            }
            probing++;
            index = (hashFunction(key) + probing * probing) % size; // Quadratic probing
            if (probing > size) {
                std::cout << "Max probing limit reached!\n";
                return;
            }
        }

        // Insert the key and update occupancy
        table[index] = key;
        occupied[index] = true;
        tombstone[index] = false; // Mark as no tombstone
        currentSize++;
    }

    // Remove function
    void remove(int key) {
        int index = hashFunction(key);
        int probing = 0;

        while (occupied[index]) {
            if (table[index] == key && !tombstone[index]) {
                tombstone[index] = true; // Mark as deleted
                currentSize--; // Decrease the count of active elements
                return;
            }
            probing++;
            index = (hashFunction(key) + probing * probing) % size;
            if (probing > size) {
                std::cout << "Element not found\n";
                return;
            }
        }
        std::cout << "Element not found\n";
    }

    // Search function
    int search(int key) {
        int index = hashFunction(key);
        int probing = 0;

        while (occupied[index]) {
            if (table[index] == key && !tombstone[index]) {
                return index; // Key found
            }
            probing++;
            index = (hashFunction(key) + probing * probing) % size;
            if (probing > size) {
                return -1; // Key not found
            }
        }
        return -1; // Key not found
    }

    // Print the table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (occupied[i] && !tombstone[i]) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << "\n";
    }
};

