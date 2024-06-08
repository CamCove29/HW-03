#include <iostream>


struct HashNode {
    int key;
    int value;
    HashNode* next;
    
    HashNode(int k, int v) : key(k), value(v), next(nullptr) {}
};

class HashMap {
private:
    HashNode** table;
    int capacity;

    // Función de hash
    int hashFunction(int key) {
        return key % capacity;
    }

public:
    HashMap(int size = 10) : capacity(size) {
        table = new HashNode*[capacity]();
    }

    void insert(int key, int value) {
        int index = hashFunction(key);
        HashNode* newNode = new HashNode(key, value);
        
        if (!table[index]) {
            table[index] = newNode;
        } else {
            HashNode* current = table[index];
            while (current->next)
                current = current->next;
            current->next = newNode;
        }
    }

    int get(int key) {
        int index = hashFunction(key);
        HashNode* current = table[index];
        while (current) {
            if (current->key == key)
                return current->value;
            current = current->next;
        }
        return -1; 
    }

    void remove(int key) {
        int index = hashFunction(key);
        HashNode* current = table[index];
        HashNode* prev = nullptr;
        while (current) {
            if (current->key == key) {
                if (!prev)
                    table[index] = current->next;
                else
                    prev->next = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    ~HashMap() {
        for (int i = 0; i < capacity; ++i) {
            HashNode* current = table[i];
            while (current) {
                HashNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }
};


