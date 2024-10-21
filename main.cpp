#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class HashTable {
private:
    vector<int> table;
    int size; // current size of the table
    int count; // number of elements in the table
    const double loadFactorThreshold = 0.8; // Threshold for resizing

    // Function to find the next prime number >= n
    int nextPrime(int n) {
        while (!isPrime(n)) {
            n++;
        }
        return n;
    }

    // Check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }

    // Hash function (key mod size)
    int hash(int key) {
        return key % size;
    }

    // Resize the table to the next prime number greater than or equal to twice its current size
    void resizeTable() {
        int newSize = nextPrime(size * 2);
        vector<int> newTable(newSize, -1); // Initialize new table with -1 (indicating empty slots)
        
        // Rehash all elements into the new table
        for (int i = 0; i < size; i++) {
            if (table[i] != -1) {
                int newHash = table[i] % newSize;
                int j = 0;
                while (newTable[(newHash + j * j) % newSize] != -1) {
                    j++;
                }
                newTable[(newHash + j * j) % newSize] = table[i];
            }
        }

        table = newTable;
        size = newSize;
    }

public:
    // Constructor to initialize the table with a prime size
    HashTable(int initialSize) {
        size = nextPrime(initialSize);
        table.resize(size, -1);
        count = 0;
    }

    // Insert a key into the hash table
    void insert(int key) {
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        // Check if resizing is needed
        if ((double)count / size >= loadFactorThreshold) {
            resizeTable();
        }

        int index = hash(key);
        int i = 0;
        while (i < size) {
            int newIndex = (index + i * i) % size;
            if (table[newIndex] == -1) { // Empty slot found
                table[newIndex] = key;
                count++;
                return;
            }
            i++;
        }
        cout << "Max probing limit reached!" << endl;
    }

    // Remove a key from the hash table
    void remove(int key) {
        int index = search(key);
        if (index == -1) {
            cout << "Element not found" << endl;
        } else {
            table[index] = -1; // Mark as deleted by setting it to -1
            count--;
        }
    }

    // Search for a key in the hash table, return the index if found, otherwise -1
    int search(int key) {
        int index = hash(key);
        int i = 0;
        while (i < size) {
            int newIndex = (index + i * i) % size;
            if (table[newIndex] == key) {
                return newIndex;
            }
            if (table[newIndex] == -1) {
                return -1; // Not found and hit an empty spot
            }
            i++;
        }
        return -1;
    }

    // Print the entire table
    void printTable() {
        for (int i = 0; i < size; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
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

    int find = ht.search(22);
    cout << "Found at:" << find <<endl;

    return 0;
}
