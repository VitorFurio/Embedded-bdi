// Em Communicator.h

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "hash_table.h"
#include "mqtt_functions.h"

class Communicator {
private:
    static HashTable* _table;
    static MQTTClient* _client;

public:
    // Construtor que recebe um ponteiro para um objeto HashTable
    Communicator();
    Communicator(HashTable* hashTable);
    
    void setClient(MQTTClient* client);
    
    // Métodos para manipular a tabela hash
    void addItemToHashTable(const std::string& name, uint8_t number, bool status);
    Item* searchItemByName(const std::string& name);
    Item* searchItemByNumber(uint8_t number);
    void updateItemStatus(const std::string& name, bool newStatus);
    void printHashTable();
    static bool internal_action_broadcast();

    //uint8_t Communicator::getNumberByName(const std::string& name);
    // Destrutor
    ~Communicator();
};

#endif // COMMUNICATOR_H

