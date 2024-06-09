//PRIMERA FORMA DE IMPLEMENTACIÓN

#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct Node {
    string key;
    int value;
    Node* next;

    Node(string k, int v) : key(k), value(v), next(nullptr) {}
};

class HashTable {
private:
    vector<Node*> table;
    int capacity;
    int size;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash = (hash * 31 + ch) % capacity;
        }
        return hash;
    }

public:
    HashTable(int cap) : capacity(cap), size(0) {
        table.resize(capacity, nullptr);
    }

    ~HashTable() {
        for (Node* head : table) {
            while (head) {
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
    }

    void insert(const string& key, int value) {
        int index = hashFunction(key);

        if (table[index] == nullptr) {
            table[index] = new Node(key, value);
        } else {
            Node* head = table[index];
            while (head->next) {
                if (head->key == key) {
                    head->value = value;
                    return;
                }
                head = head->next;
            }
            if (head->key == key) {
                head->value = value;
            } else {
                head->next = new Node(key, value);
            }
        }
        size++;
    }
    int search(const string& key) {
        int index = hashFunction(key);
        Node* head = table[index];

        while (head) {
            if (head->key == key) {
                return head->value;
            }
            head = head->next;
        }

        throw runtime_error("Clave no encontrada");
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        Node* head = table[index];
        Node* prev = nullptr;

        while (head) {
            if (head->key == key) {
                if (prev == nullptr) {
                    table[index] = head->next;
                } else {
                    prev->next = head->next;
                }
                delete head;
                size--;
                return;
            }
            prev = head;
            head = head->next;
        }

        throw runtime_error("Clave no encontrada");
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }
};

