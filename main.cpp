#include "HashTable.cpp"

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

    bool found = ht.search(22);  // Change from int to bool
    std::cout << "Found 22: " << (found ? "true" : "false") << std::endl; // Update output

    return 0;
}