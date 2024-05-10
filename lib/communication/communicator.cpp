// Em Communicator.cpp

#include "communicator.h"
#include <iostream>
#include <sstream>
#include <string>

HashTable* Communicator::_table = nullptr; //Deletar

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

void parseMessage(const std::string& message, std::string& command, std::string& content) {
    std::istringstream iss(message);
    std::getline(iss, command, '/');
    std::getline(iss, content);
}

CENUMFOR_ILF stringToILF(const std::string& string) {
    if (string == "TELL") {
        return CENUMFOR_ILF::TELL;
    } else if (string == "UNTELL") {
        return CENUMFOR_ILF::UNTELL;
    } else if (string == "ACHIEVE") {
        return CENUMFOR_ILF::UNTELL;
    } else {
        return CENUMFOR_ILF::TELL;
    }
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

void Communicator::update(BeliefBase * belief_base, EventBase * event_base)
{
  if (belief_base && event_base) 
  {
    Item_list* current = _list->getHead();
   while (current != nullptr)
   {
        if (current->status == true) //Recebeu mensagem -> atualiza eventos
        { 
            if (!event_base->is_full())
            {
                Proposition prop;
                Event event;
                switch (current->ilf) 
                {
                    case CENUMFOR_ILF::TELL:
                        prop = Proposition(current->number);
                        event = Event(EventOperator::BELIEF_ADDITION, prop);
                        belief_base->change_belief_state(prop, true);
                        event_base->add_event(event);
                        current->status = false;
                        break;
                    case CENUMFOR_ILF::UNTELL:
                        //printf("\n UNTELL não implementado\n");
                        break;
                    case CENUMFOR_ILF::ACHIEVE:
                        //printf("\n ACHIEVE não implementado\n");
                        break;
                    default:
                        std::cout << "Erro na recepção da mensagem: " << current->name << std::endl;
                }
            }
        }
       current = current->next;
   }
  }
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

// ## Funções para manipular o protocolo MQTT: 

// Callback chamada quando uma mensagem é recebida
int Communicator::messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    printf("Message arrived on topic \"%s\": %.*s\n", topicName, message->payloadlen, (char *)message->payload);
    std::string msg_ilf, msg_prop;
    parseMessage((char *)message->payload, msg_ilf, msg_prop);
    //std::cout << "ILF da mensagem: " << msg_ilf << std::endl;
    //std::cout << "Prop da mensagem: " << msg_prop << std::endl;
    Item_list* item = _list->searchByName(msg_prop);
    item->status = true;
    item->ilf = stringToILF(msg_ilf);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

// Setup inicial: criação do cliente MQTT e conexão ao broker MQTT
int Communicator::setup_mqtt_client(MQTTClient *client) {
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    MQTTClient_create(client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    if ((rc = MQTTClient_setCallbacks(*client, NULL, NULL, Communicator::messageArrived, NULL)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to set callbacks, return code %d\n", rc);
        return -1;
    }
    if ((rc = MQTTClient_connect(*client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        return -1;
    }
    printf("Connected to %s\n", ADDRESS);
    return 0;
}

int Communicator::subscribe_topic(MQTTClient *client_ptr, const char *topic) {
    int rc;
    if ((rc = MQTTClient_subscribe(*client_ptr, topic, QOS)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to subscribe to topic \"%s\", return code %d\n", topic, rc);
        return -1;
    }
    printf("Subscribed to topic \"%s\"\n", topic);
    return 0;
}

// Funcionalidade: publicação de uma mensagem em um tópico MQTT
int Communicator::publish_message(MQTTClient client, const char *topic, const char *message) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;
    pubmsg.payload = (void *)message;
    pubmsg.payloadlen = strlen(message);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    if ((rc = MQTTClient_publishMessage(client, topic, &pubmsg, &token)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to publish message to topic \"%s\", return code %d\n", topic, rc);
        return -1;
    }
    printf("Waiting for publication of \"%s\" on topic \"%s\"\n", message, topic);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    return rc;
}

int Communicator::disconnect_mqtt_client(MQTTClient client) {
    int rc;
    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to disconnect from MQTT broker, return code %d\n", rc);
        return -1;
    }
    MQTTClient_destroy(&client);
    printf("Disconnected from MQTT broker\n");
    return 0;
}