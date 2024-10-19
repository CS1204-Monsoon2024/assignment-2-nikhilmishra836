#include "HashTable.cpp"

int main() {
    int initialSize = 7; 
    HashTable ht(initialSize);

    ht.insert(1);
    ht.insert(6);
    ht.insert(15);
    ht.insert(25);
    ht.remove(15);
    ht.insert(29); 

    int find = ht.search(22);
    std::cout << "Found at: " << find << std::endl;

    return 0;
}
