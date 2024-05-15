#include "mqtt_functions.h"
#include <iostream>

MQTTClient MQTTFunctions::_client = nullptr;

void MQTTFunctions::initializeClient() {
    setup_mqtt_client(&_client);
    subscribe_topic("Hello");
    subscribe_topic("Agent1");
    subscribe_topic("broadcast");
    std::cout << "Cliente MQTT configurado com sucesso." << std::endl;
}

int MQTTFunctions::setup_mqtt_client(MQTTClient* client) {
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_create(client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    int rc = MQTTClient_setCallbacks(*client, NULL, NULL, messageArrived, NULL);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Falha ao definir callbacks, código de retorno " << rc << std::endl;
        return -1;
    }
    rc = MQTTClient_connect(*client, &conn_opts);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Falha ao conectar, código de retorno " << rc << std::endl;
        return -1;
    }
    std::cout << "Conectado ao broker MQTT em " << ADDRESS << std::endl;
    return 0;
}

int MQTTFunctions::subscribe_topic(const std::string& topic) {
    int rc = MQTTClient_subscribe(_client, topic.c_str(), QOS);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Falha ao inscrever-se no tópico \"" << topic << "\", código de retorno " << rc << std::endl;
        return -1;
    }
    std::cout << "Inscrito no tópico \"" << topic << "\"" << std::endl;
    return 0;
}

int MQTTFunctions::publish_message(const std::string& topic, const std::string& message) {
    if (!_client || !MQTTClient_isConnected(_client)) {
        std::cerr << "Cliente MQTT não inicializado ou desconectado." << std::endl;
        return -1;
    }
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = (void*)message.c_str();
    pubmsg.payloadlen = message.length();
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    int rc = MQTTClient_publishMessage(_client, topic.c_str(), &pubmsg, &token);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Falha ao publicar mensagem no tópico \"" << topic << "\", código de retorno " << rc << std::endl;
        return -1;
    }
    MQTTClient_waitForCompletion(_client, token, TIMEOUT);
    //std::cout << "Mensagem entregue com token de entrega " << token << std::endl;
    return 0;
}

int MQTTFunctions::messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message) {
    std::string msg((char*)message->payload, message->payloadlen);
    std::cout << "Mensagem chegou no tópico \"" << topicName << "\": " << msg << std::endl;
    Communicator::messageArrived(msg);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

int MQTTFunctions::disconnect_mqtt_client() {
    if (!_client) {
        std::cerr << "Cliente MQTT não inicializado." << std::endl;
        return -1;
    }
    int rc = MQTTClient_disconnect(_client, 10000);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Falha ao desconectar do broker MQTT, código de retorno " << rc << std::endl;
        return -1;
    }
    MQTTClient_destroy(&_client);
    std::cout << "Desconectado do broker MQTT." << std::endl;
    return 0;
}
