#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table; // The table is a series of hash maps
    int size; // Size of the hash map
    int currentSize; // Current size of the hash map
    double loadFactor; // Load factor threshold

    // Function to check if a number is prime
    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    // Get the next prime number greater than or equal to num
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

    // Resize the hash table
    void resize() {
        int oldSize = size;
        size = nextPrime(size * 2); // Resize to at least double the size
        std::vector<int> oldTable = table;

        table = std::vector<int>(size, -1); // Initialize new table
        currentSize = 0; // Reset current size

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != -1) {
                insert(oldTable[i]); // Rehash the old keys
            }
        }
    }

public:
    // Constructor
    HashTable(int initialSize) : size(nextPrime(initialSize)), loadFactor(0.8), currentSize(0) {
        table.resize(size, -1); // Initialize table
    }

    // Insert function
    void insert(int key) {
        if ((double)currentSize / size >= loadFactor) {
            resize(); // Resize if load factor exceeds threshold
        }

        int index = hashFunction(key);
        int i = 1;

        while (table[index] != -1) {
            if (table[index] == key) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return;
            }
            index = (hashFunction(key) + i * i) % size; // Quadratic probing
            i++;
            if (i > size) {
                std::cout << "Max probing limit reached!\n";
                return;
            }
        }

        table[index] = key; // Insert the key
        currentSize++;
    }

    // Remove function
    void remove(int key) {
        int index = hashFunction(key);
        int i = 1;

        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1; // Mark as deleted
                return;
            }
            index = (hashFunction(key) + i * i) % size; // Quadratic probing
            i++;
            if (i > size) {
                std::cout << "Element not found\n";
                return;
            }
        }
        std::cout << "Element not found\n"; // Key not found
    }

    // Search function
    int search(int key) {
        int index = hashFunction(key);
        int i = 1;

        while (table[index] != -1) {
            if (table[index] == key) {
                return index; // Return the index if found
            }
            index = (hashFunction(key) + i * i) % size; // Quadratic probing
            i++;
            if (i > size) {
                return -1; // Not found
            }
        }
        return -1; // Not found
    }

    // Print the hash table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != -1) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << "\n"; // New line after printing the table
    }
};
