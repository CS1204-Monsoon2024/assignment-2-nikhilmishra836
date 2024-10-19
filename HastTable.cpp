#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Prime number checking function
bool isPrime(int num) {
    if (num < 2) return false;  // Edge cases: numbers less than 2 are not prime

    // Handle small prime numbers directly
    if (num == 2 || num == 3) return true;
    if (num % 2 == 0 || num % 3 == 0) return false;  // Not prime if divisible by 2 or 3

    // Check divisibility by numbers greater than 3
    for (int i = 5; i * i <= num; i += 6) {  // Only check up to square root of num
        if (num % i == 0 || num % (i + 2) == 0) return false;
    }
    return true;  // It's prime
}

// Function to find the next prime number greater than a given number
int nextPrimefinder(int num) {
    while (!isPrime(num)) {  // Increment num until a prime is found
        num++;
    }
    return num;
}

class HashTable {
private:
    vector<int> table;  // The hash table will dynamically resize
    int m;  // The size of the table
    int elements_num;  // The number of elements currently in the table
    const double upperloadfactor = 0.8;  // Load factor threshold for resizing

    // Simple hash function
    int hashfunction(int key) {
        return key % m;
    }

    // Function to resize the table when the load factor exceeds the threshold
    void resizingtable() {
        int oldsize = m;
        m = nextPrimefinder(2 * oldsize);  // Find the next prime number after doubling the size

        vector<int> newtable(m, -1);  // Create a new table with the new size, initialized to -1

        // Rehash the old elements into the new table
        for (int i = 0; i < oldsize; i++) {
            if (table[i] != -1) {  // If the slot is not empty, rehash the element
                int newIndex = hashfunction(table[i]);
                int j = 0;

                // Quadratic probing to resolve collisions
                while (newtable[newIndex] != -1) {  // While the element in the new slot is not empty
                    j++;  // Probe value changes
                    newIndex = (newIndex + j * j) % m;
                }
                newtable[newIndex] = table[i];  // Insert the element in the new slot
            }
        }
        table = newtable;  // Replace the old table with the resized table
    }

public:
    // Constructor
    HashTable(int size) {
        if (isPrime(size)) {
            m = size;  // This is the size of the table
        } else {
            m = nextPrimefinder(size);  // If not prime, find the next prime number
        }
        table.resize(m, -1);  // Resize it to size m, with each element initialized to -1
        elements_num = 0;  // Initially empty
    }

    // Inserting a key into the hash table
    void insert(int key) {
        // Check if the table needs to be resized
        if ((double)elements_num / m > upperloadfactor) {
            resizingtable();  // Resize the hashtable
        }

        // Finding the hash index for the key 
        int index = hashfunction(key);
        int i = 0;  // Counter for quadratic probing
        int newIndex = index;  // Initialize newIndex

        // Quadratic probing to find empty slot 
        while (table[newIndex] != -1 && table[newIndex] != -2) {  // While the new index is not empty and not a tombstone
            i++; 
            newIndex = (index + i * i) % m;  // Quadratic probing to find next slot if full
        }

        table[newIndex] = key;  // Inserting key
        elements_num++;  // Increment number of elements
    }

    // Searching for a key 
    bool search(int key) {
        int index = hashfunction(key);
        int i = 0;  // Quadratic probing counter
        int newIndex = index;  // Initialize newIndex

        // Probing for the key
        while (table[newIndex] != -1) {  // If the current index is not empty
            if (table[newIndex] == key) {  // Compare the key in the current slot with the key to find
                return true;  // Return true if found
            }
            i++;  // Increment probe counter
            newIndex = (index + i * i) % m;  // Update newIndex for probing
        }
        return false;  // Return false if not found
    }

    // Removing a key
    void remove(int key) {
        int index = hashfunction(key);
        int i = 0;  // Quadratic probing counter
        int newIndex = index;  // Initialize newIndex

        // Doing the probing
        while (table[newIndex] != -1) {
            if (table[newIndex] == key) {  // If the key is found
                table[newIndex] = -2;  // Mark as deleted (tombstone)
                elements_num--;  // Decrement number of elements
                return;  // Exit after deletion
            }
            i++;  // Increment probe counter
            newIndex = (index + i * i) % m;  // Update newIndex for probing
        }
    }
};

// Main function
int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.insert(6);
    ht.insert(15);
    ht.insert(25);
    ht.remove(15);
    ht.insert(29);  

    // Searching for a key
    bool found = ht.search(22);
    std::cout << "Found: " << (found ? "true" : "false") << std::endl;

    return 0;
}
