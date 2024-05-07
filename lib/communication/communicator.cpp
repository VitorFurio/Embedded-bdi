// Em Communicator.cpp

#include "communicator.h"

HashTable* Communicator::_table = nullptr;
MQTTClient* Communicator::_client = nullptr;

Communicator::Communicator() {}
Communicator::Communicator(HashTable* hashTable) {
    _table = hashTable;
   // MQTTClient_create(client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL); //#ERRO de falha de segmentação se declarado aqui!
}

void Communicator::setClient(MQTTClient* client){
     if (setup_mqtt_client(client) != 0) {
         std::cout << "ERROR: Falha ao inicializar o cliente MQTT.\n" << std::endl;
    }
    _client = client;
    subscribe_topic(client, "Hello");
    subscribe_topic(client, "Agent1");
    std::cout << "Cliente configurado!\n" << std::endl;
}

void Communicator::addItemToHashTable(const std::string& name, uint8_t number, bool status) {
    _table->addItem(name, number, status);
}

Item* Communicator::searchItemByName(const std::string& name) {
    return _table->searchByName(name);
}

Item* Communicator::searchItemByNumber(uint8_t number) {
    return _table->searchByNumber(number);
}

void Communicator::updateItemStatus(const std::string& name, bool newStatus) {
    _table->updateStatus(name, newStatus);
}

void Communicator::printHashTable() {
    _table->print();
}

bool Communicator::internal_action_broadcast()
{
  std::cout << "Communicator Broadcast!" << std::endl;
  std::cout << "Valores da proposição hello:" << std::endl;
  std::cout << "Name: " << _table->searchByName("happy")->getName() << std::endl;
  std::cout << "Status: " << _table->searchByName("happy")->getStatus() << std::endl;
  std::cout << "Number: " << static_cast<int>(_table->searchByName("happy")->getNumber()) << std::endl;
  //_table->print();
  return true;
}

Communicator::~Communicator() {}
