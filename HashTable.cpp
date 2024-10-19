#include "HashTable.cpp"

int main() {
    int initialSize = 7; // example size
    HashTable ht(initialSize);

    // Insert elements
    ht.insert(3);
    ht.insert(13);
    ht.insert(20);
    ht.insert(4);
    ht.insert(21);
    
    ht.printTable();

    // Test search and remove
    int found = ht.search(20);
    cout << "Found at: " << found << endl;

    ht.remove(20);
    ht.printTable();

    found = ht.search(20);
    cout << "Found at: " << found << endl;
    
    return 0;
}
