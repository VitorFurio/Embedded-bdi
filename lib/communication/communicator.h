// Em Communicator.h

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "hash_table.h"
#include "msg_list.h"
#include "../bdi/belief.h"
#include "../bdi/belief_base.h"
#include "../bdi/event.h"
#include "../bdi/event_base.h"
#include "../syntax/cenumfor_ilf.h"
#include "../syntax/proposition.h"

//#include "mqtt_functions.h"
#include "MQTTClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDRESS     "mqtt://mqtt.eclipseprojects.io"
#define CLIENTID    "AgentSender"
#define QOS         1
#define TIMEOUT     10000L

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
    void update(BeliefBase * belief_base, EventBase * event_base);
    
  //  void printHashTable();
    
    // Métodos para as ações internas de comunicação
    static bool internal_action_broadcast();

    //uint8_t Communicator::getNumberByName(const std::string& name);
    // Destrutor
    ~Communicator();


// ## Funções para manipular o protocolo MQTT: 
    int setup_mqtt_client(MQTTClient *client);
    int subscribe_topic(MQTTClient *client_ptr, const char *topic);
    int publish_message(MQTTClient client, const char *topic, const char *message);
    int disconnect_mqtt_client(MQTTClient client);
    static int messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
    
};

#endif // COMMUNICATOR_H

