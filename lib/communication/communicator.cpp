// Em Communicator.cpp

#include "communicator.h"

HashTable* Communicator::table = nullptr;

Communicator::Communicator(HashTable* hashTable) {
    table = hashTable;
}

void Communicator::addItemToHashTable(const std::string& name, uint8_t number, bool status) {
    table->addItem(name, number, status);
}

Item* Communicator::searchItemByName(const std::string& name) {
    return table->searchByName(name);
}

Item* Communicator::searchItemByNumber(uint8_t number) {
    return table->searchByNumber(number);
}

void Communicator::updateItemStatus(const std::string& name, bool newStatus) {
    table->updateStatus(name, newStatus);
}

void Communicator::printHashTable() {
    table->print();
}

bool Communicator::internal_action_broadcast()
{
  std::cout << "Communicator Broadcast!" << std::endl;
  std::cout << "Valores da proposição hello:" << std::endl;
  std::cout << "Name: " << table->searchByName("happy")->getName() << std::endl;
  std::cout << "Status: " << table->searchByName("happy")->getStatus() << std::endl;
  std::cout << "Number: " << static_cast<int>(table->searchByName("happy")->getNumber()) << std::endl;
  //table->print();
  return true;
}

Communicator::~Communicator() {}
