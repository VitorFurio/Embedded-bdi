// HashTable.cpp

#include "hash_table.h"

Item::Item(const std::string& itemName, uint8_t itemNumber, bool itemStatus) // Atualizado
    : name(itemName), number(itemNumber), status(itemStatus) {}

const std::string& Item::getName() const { return name; }

uint8_t Item::getNumber() const { return number; }

bool Item::getStatus() const { return status; } // Atualizado

void Item::setStatus(bool newStatus) { status = newStatus; } // Atualizado

unsigned int HashTable::hash(const std::string& key) {
    unsigned int hashValue = 0;
    for (char c : key) {
        hashValue = 31 * hashValue + c;
    }
    return hashValue % HASH_SIZE;
}

void HashTable::addItem(const std::string& name, uint8_t number, bool status) { // Atualizado
    unsigned int index = hash(name);
    Item* newItem = new Item(name, number, status);
    hashTable[index].push_back(newItem);
}

Item* HashTable::searchByName(const std::string& name) {
    unsigned int index = hash(name);
    for (Item* item : hashTable[index]) {
        if (item->getName() == name) {
            return item;
        }
    }
    return nullptr;
}

Item* HashTable::searchByNumber(uint8_t number) {
    for (const auto& bucket : hashTable) {
        for (Item* item : bucket) {
            if (item->getNumber() == number) {
                return item;
            }
        }
    }
    return nullptr;
}

void HashTable::updateStatus(const std::string& name, bool newStatus) { // Atualizado
    Item* itemToUpdate = searchByName(name);
    if (itemToUpdate != nullptr) {
        itemToUpdate->setStatus(newStatus);
    } else {
        std::cout << "Item '" << name << "' não encontrado." << std::endl;
    }
}

void HashTable::print() {
    for (int i = 0; i < HASH_SIZE; ++i) {
        std::cout << "Bucket " << i << ": ";
        for (Item* item : hashTable[i]) {
            std::cout << "Name: " << item->getName() << ", ";
            std::cout << "Number: " << static_cast<int>(item->getNumber()) << ", ";
            std::cout << "Status: " << (item->getStatus() ? "true" : "false") << "; ";
        }
        std::cout << std::endl;
    }
}

int HashTable::size() const {
    return HASH_SIZE;
}

HashTable::~HashTable() {
    for (auto& bucket : hashTable) {
        for (Item* item : bucket) {
            delete item;
        }
    }
}
