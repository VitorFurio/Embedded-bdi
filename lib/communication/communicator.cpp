// Em Communicator.cpp

#include "communicator.h"

HashTable* Communicator::_table = nullptr;
MsgList* Communicator::_list= nullptr;
MQTTClient* Communicator::_client = nullptr;
Belief* Communicator::_belief = nullptr;

Communicator::Communicator() {}
Communicator::Communicator(HashTable* hashTable) {
    _table = hashTable;
}
Communicator::Communicator(MsgList* list) {
    _list = list;
}

void Communicator::setClient(MQTTClient* client){
     if (setup_mqtt_client(client) != 0) {
         std::cout << "ERROR: Falha ao inicializar o cliente MQTT.\n" << std::endl;
    }
    _client = client;
    subscribe_topic(client, "Hello"); //TODO: Fução de se increver em um tópico. Validar se ela ocorreu corretamente.
    subscribe_topic(client, "Agent1");
    std::cout << "Cliente configurado!\n" << std::endl;
}


//void Communicator::printHashTable() {
//    _table->print();
//}

// bool Communicator::internal_action_broadcast()
// {
//   std::cout << "Communicator Broadcast!" << std::endl;
//   std::cout << "Valores da proposição happy:" << std::endl;
//   std::cout << "Name: " << _table->searchByName("happy")->getName() << std::endl;
//   std::cout << "Status: " << _table->searchByName("happy")->getStatus() << std::endl;
//   //std::cout << "Number: " << static_cast<int>(_table->searchByName("happy")->getNumber()) << std::endl;
//   printf("Number: %u\n\n", _table->searchByName("happy")->getNumber());
//   //_table->print();
//   return true;
// }

bool Communicator::internal_action_broadcast()
{
  std::cout << "Communicator Broadcast!" << std::endl;
  std::cout << "Valores da proposição happy:" << std::endl;
  std::cout << "Name: " << _list->searchByName("happy")->name << std::endl;
  std::cout << "Status: " << _list->searchByName("happy")->status << std::endl;
  printf("Number: %u\n\n", _list->searchByName("happy")->number);
  _list->print();
  return true;
}

Communicator::~Communicator() {}
