#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>

class HashTable {
private:
    std::vector<int> table;
    std::vector<bool> isOccupied;
    size_t size;
    size_t currentSize;
    double loadFactor;

    bool isPrime(size_t num) {
        if (num <= 1) return false;
        for (size_t i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    size_t nextPrime(size_t num) {
        while (!isPrime(num)) {
            num++;
            if (num == 0) throw std::overflow_error("Integer overflow in nextPrime");
        }
        return num;
    }

    size_t hashFunction(int key) {
        return static_cast<size_t>(std::abs(static_cast<long long>(key))) % size;
    }

    void resize() {
        size_t oldSize = size;
        size = nextPrime(size * 2);
        if (size <= oldSize) throw std::overflow_error("Integer overflow in resize");

        std::vector<int> oldTable = std::move(table);
        std::vector<bool> oldOccupied = std::move(isOccupied);

        table = std::vector<int>(size);
        isOccupied = std::vector<bool>(size, false);
        currentSize = 0;

        for (size_t i = 0; i < oldSize; i++) {
            if (oldOccupied[i]) {
                insert(oldTable[i]);
            }
        }
    }

public:
    HashTable(size_t initialSize) : size(nextPrime(initialSize)), loadFactor(0.8), currentSize(0) {
        if (initialSize == 0) throw std::invalid_argument("Initial size cannot be 0");
        table.resize(size);
        isOccupied.resize(size, false);
    }

    void insert(int key) {
        if (static_cast<double>(currentSize) / size >= loadFactor) {
            resize();
        }

        size_t index = hashFunction(key);
        size_t i = 0;

        while (isOccupied[index]) {
            if (table[index] == key) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return;
            }
            i++;
            if (i >= size) {
                throw std::runtime_error("Hash table is full");
            }
            index = (hashFunction(key) + i * i) % size;
        }

        table[index] = key;
        isOccupied[index] = true;
        currentSize++;
    }

    void remove(int key) {
        size_t index = hashFunction(key);
        size_t i = 0;

        while (isOccupied[index]) {
            if (table[index] == key) {
                isOccupied[index] = false;
                // Note: We don't decrease currentSize here
                return;
            }
            i++;
            if (i >= size) {
                std::cout << "Element not found\n";
                return;
            }
            index = (hashFunction(key) + i * i) % size;
        }
        std::cout << "Element not found\n";
    }

    bool search(int key) {
        size_t index = hashFunction(key);
        size_t i = 0;

        while (isOccupied[index] || i < size) {
            if (isOccupied[index] && table[index] == key) {
                return true;
            }
            i++;
            if (i >= size) {
                return false;
            }
            index = (hashFunction(key) + i * i) % size;
        }
        return false;
    }

    void printTable() {
        for (size_t i = 0; i < size; i++) {
            if (isOccupied[i]) {
                std::cout << table[i] << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << "\n";
    }

    double getCurrentLoadFactor() {
        return static_cast<double>(currentSize) / size;
    }
};