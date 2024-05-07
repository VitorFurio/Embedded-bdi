// Em Communicator.cpp

#include "communicator.h"

HashTable* Communicator::_table = nullptr;
MQTTClient* Communicator::_client = nullptr;
Belief* Communicator::_belief = nullptr;

Communicator::Communicator() {}
Communicator::Communicator(HashTable* hashTable) {
    _table = hashTable;
}

void Communicator::setClient(MQTTClient* client){
     if (setup_mqtt_client(client) != 0) {
         std::cout << "ERROR: Falha ao inicializar o cliente MQTT.\n" << std::endl;
    }
    _client = client;
    subscribe_topic(client, "Hello"); //TODO: Funão de se increver em um tópico.
    subscribe_topic(client, "Agent1");
    std::cout << "Cliente configurado!\n" << std::endl;
}

//void Communicator::add_arg(Belief* belief){
 //   _belief
//}

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
  std::cout << "Valores da proposição happy:" << std::endl;
  std::cout << "Name: " << _table->searchByName("happy")->getName() << std::endl;
  std::cout << "Status: " << _table->searchByName("happy")->getStatus() << std::endl;
  //std::cout << "Number: " << static_cast<int>(_table->searchByName("happy")->getNumber()) << std::endl;
  printf("Number: %u\n\n", _table->searchByName("happy")->getNumber());
  //_table->print();
  return true;
}

Communicator::~Communicator() {}
