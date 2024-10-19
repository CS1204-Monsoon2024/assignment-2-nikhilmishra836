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
int nextPrimeFinder(int num) {
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
    int hashFunction(int key) {
        return key % m;
    }

    // Function to resize the table when the load factor exceeds the threshold
    void resizingTable() {
        int oldsize = m;
        m = nextPrimeFinder(2 * oldsize);  // Find the next prime number after doubling the size

        vector<int> newTable(m, -1);  // Create a new table with the new size, initialized to -1

        // Rehash the old elements into the new table
        for (int i = 0; i < oldsize; i++) {
            if (table[i] != -1 && table[i] != -2) {  // If the slot is not empty and not deleted, rehash the element
                int newIndex = hashFunction(table[i]);
                int j = 0;

                // Quadratic probing to resolve collisions
                while (newTable[newIndex] != -1) { // while the element in the new slot is not empty - keep rehashing until it is
                    j++; // probe value changes
                    newIndex = (newIndex + j * j) % m;
                }
                newTable[newIndex] = table[i];  // Insert the element in the new slot
            }
        }
        table = newTable;  // Replace the old table with the resized table
    }

public:
    // Constructor
    HashTable(int size) {
        if (isPrime(size)) {
            m = size;  // This is the size of the table
        } else {
            m = nextPrimeFinder(size); // if not prime - find the next prime number
        }
        table.resize(m, -1); // Resize it to size m - with each element at -1 value
        elements_num = 0; // It is initially empty
    }

    // Inserting a key into the hash table
    void insert(int key) {
        // First check if the table needs to be resized
        if ((double)elements_num / m > upperloadfactor) {
            resizingTable(); // Resize the hashtable
        }

        // Finding the hash index for the key 
        int index = hashFunction(key); 
        int i = 0; // Counter for quadratic probing 
        int newIndex = index;  // Initialize newIndex

        // Quadratic probing to find an empty slot 
        while (table[newIndex] != -1 && table[newIndex] != -2) { // While the new index is occupied and not a tombstone
            i++;
            newIndex = (index + i * i) % m; // Quadratic probing to find next slot if full 
        }

        table[newIndex] = key; // Inserting key 
        elements_num++; // Number of elements increases by 1
    }

    // Searching for a key 
    bool search(int key) {
        int index = hashFunction(key);
        int i = 0;
        int newIndex = index;

        // Probing for later searches 
        while (table[newIndex] != -1) { // If the current index is not empty
            if (table[newIndex] == key) { // Compare the key in the current slot in the table
                return true; // Found the key
            }
            i++; // Increment probe counter for subsequent probing
            newIndex = (index + i * i) % m; // Update newIndex with probing
        }
        return false; // Key not found
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = hashFunction(key);
        int i = 0; // Quadratic probing counter
        int newIndex = index;

        // Doing the probing
        while (table[newIndex] != -1) {
            if (table[newIndex] == key) { // If the key is found
                table[newIndex] = -2; // Mark the slot as deleted
                elements_num--; // Decrease the number of elements
                return; // Exit the function
            }
            i++;
            newIndex = (index + i * i) % m; // Update newIndex with probing
        }
    }

    // Print the current state of the hash table
    void printTable() const {
        cout << "Hash Table: ";
        for (int i = 0; i < m; i++) {
            if (table[i] == -1) {
                cout << "[-] "; // Empty slot
            } else if (table[i] == -2) {
                cout << "[X] "; // Deleted slot (tombstone)
            } else {
                cout << "[" << table[i] << "] "; // Current element
            }
        }
        cout << endl;
    }
};

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    // Example test case
    ht.insert(1);
    ht.printTable();
    ht.insert(6);
    ht.printTable();
    ht.insert(15);
    ht.printTable(); 
    ht.insert(25);
    ht.printTable();
    ht.remove(15);
    ht.printTable();
    ht.insert(29);  
    ht.printTable(); 

    // Searching for a key
    bool find = HashTable.search(22); // Search for key 22
    std::cout << "Found at: " << (find ? "true" : "false") << std::endl; // Print result of the search

    return 0;
}
