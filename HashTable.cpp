#include <iostream>
#include <vector>

class HashTable {
private:
    std::vector<int> table;
    int size;
    int currentSize;
    double loadFactor;

    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int nextPrime(int num) {
        while (!isPrime(num)) {
            num++;
        }
        return num;
    }

    int hashFunction(int key) {
        return key % size;
    }

    void resize() {
        int oldSize = size;
        size = nextPrime(size * 2);
        std::vector<int> oldTable = table;

        table = std::vector<int>(size, -1);
        currentSize = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != -1) {
                insert(oldTable[i]);
            }
        }
    }

public:
    HashTable(int initialSize) : size(nextPrime(initialSize)), loadFactor(0.8), currentSize(0) {
        table.resize(size, -1);
    }

    void insert(int key) {
        if ((double)currentSize / size >= loadFactor) {
            resize();
        }

        int index = hashFunction(key);
        int i = 1;

        while (table[index] != -1) {
            if (table[index] == key) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return;
            }
            index = (hashFunction(key) + i * i) % size;
            i++;
            if (i > size) {
                std::cout << "Hash table is full\n";
                return;
            }
        }

        table[index] = key;
        currentSize++;
    }

    void remove(int key) {
        int index = hashFunction(key);
        int i = 1;

        while (table[index] != -1) {
            if (table[index] == key) {
                table[index] = -1; // Mark as deleted
                // Note: We don't decrease currentSize here
                return;
            }
            index = (hashFunction(key) + i * i) % size;
            i++;
            if (i > size) {
                std::cout << "Element not found\n";
                return;
            }
        }
        std::cout << "Element not found\n";
    }

    int search(int key) {
        int index = hashFunction(key);
        int i = 1;

        while (table[index] != -1) {
            if (table[index] == key) {
                return index;
            }
            index = (hashFunction(key) + i * i) % size;
            i++;
            if (i > size) {
                return -1;
            }
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] != -1) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << "\n";
    }

    double getCurrentLoadFactor() {
        return (double)currentSize / size;
    }
};