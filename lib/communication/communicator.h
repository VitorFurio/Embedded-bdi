// Em Communicator.h

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "hash_table.h"
#include "msg_list.h"
#include "mqtt_functions.h"
#include "../bdi/belief.h"
#include "../bdi/event.h"
#include "../bdi/event_base.h"
#include "../syntax/cenumfor_ilf.h"

class Communicator {
private:
    static HashTable* _table;
    static MsgList* _list;
    static MQTTClient* _client;
    
    // para envio das mensagens
    static Belief* _belief;
    CENUMFOR_ILF _ilf;
     
public:
    // Construtor que recebe um ponteiro para um objeto HashTable
    Communicator();
    Communicator(HashTable* hashTable);
    Communicator(MsgList* list);
    
    //Métodos para o utilizar o protocolo MQTT.
    void setClient(MQTTClient* client); 
    
    // Métodos para o framework BDI
    void update(EventBase * event_base);
    
  //  void printHashTable();
    
    // Métodos para as ações internas de comunicação
    static bool internal_action_broadcast();

    //uint8_t Communicator::getNumberByName(const std::string& name);
    // Destrutor
    ~Communicator();
};

#endif // COMMUNICATOR_H

