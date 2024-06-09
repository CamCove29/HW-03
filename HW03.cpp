//SEGUNDA FORMA DE IMPLEMENTACIÓN

#include <iostream>
#include <string>
using namespace std;

class HashNode {
public:
    int key;
    string name;
    HashNode* next;

    HashNode(int key, string name) {
        this->key = key;
        this->name = name;
        this->next = nullptr;
    }
};

class HashTable {
private:
    HashNode** data;
    int size;

    int HashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int size) {
        this->size = size;
        data = new HashNode*[size]();
    }

    ~HashTable() {
        for (int i = 0; i < size; ++i) {
            HashNode* current = data[i];
            while (current != nullptr) {
                HashNode* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] data;
    }

    void print() {
        for (int i = 0; i < size; ++i) {
            HashNode* current = data[i];
            while (current != nullptr) {
                cout << "Index: " << i
                     << " Key: " << current->key
                     << " Name: " << current->name
                     << endl;
                current = current->next;
            }
        }
    }

    void insert(HashNode* item) {
        int key = item->key;
        int hash = HashFunction(key);
        if (data[hash] == nullptr) {
            // No hay colisión en este índice
            data[hash] = item;
        } else {
            // Hay colisión, agregar al final de la lista
            HashNode* current = data[hash];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = item;
        }
    }

    HashNode* dato(int key) {
        int hash = HashFunction(key);
        HashNode* current = data[hash];
        while (current != nullptr) {
            if (current->key == key) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // No se encontró el nodo con la clave dada
    }
};
int main() {

    HashTable table(10);

    HashNode node1(101, "John");
    HashNode node2(201, "Alice");
    HashNode node3(302, "Bob");

    table.insert(&node1);
    table.insert(&node2);
    table.insert(&node3);

    cout << "Tabla Hash despues de la insercion:" << endl;
    table.print();

}
