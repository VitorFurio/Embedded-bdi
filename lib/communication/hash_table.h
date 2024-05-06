// hash_table.h

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

class Item {
private:
    std::string name;
    uint8_t number;
    bool status; // Alterado para bool

public:
    Item(const std::string& itemName, uint8_t itemNumber, bool itemStatus); // Atualizado
    const std::string& getName() const;
    uint8_t getNumber() const;
    bool getStatus() const; // Atualizado
    void setStatus(bool newStatus); // Atualizado
};

class HashTable {
private:
    static const int HASH_SIZE = 1000;
    std::vector<Item*> hashTable[HASH_SIZE];
    unsigned int hash(const std::string& key);

public:
    void addItem(const std::string& name, uint8_t number, bool status); // Atualizado
    Item* searchByName(const std::string& name);
    Item* searchByNumber(uint8_t number);
    void updateStatus(const std::string& name, bool newStatus); // Atualizado
    void print();
    ~HashTable();
};

#endif // HASH_TABLE_H
