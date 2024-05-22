#include "mqtt_functions.h"
#include <iostream>

MQTTClient MQTTFunctions::_client = nullptr;

void MQTTFunctions::initializeClient() {
    setup_mqtt_client(&_client);
    subscribe_topic("broadcast");
    subscribe_topic("hello");
    std::cout << "MQTT client successfully configured." << std::endl << std::endl;
}

int MQTTFunctions::setup_mqtt_client(MQTTClient* client) {
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    MQTTClient_create(client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    int rc = MQTTClient_setCallbacks(*client, NULL, NULL, messageArrived, NULL);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Failed to set callbacks, return code " << rc << std::endl;
        return -1;
    }
    rc = MQTTClient_connect(*client, &conn_opts);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Failed to connect, return code " << rc << std::endl;
        return -1;
    }
    std::cout << "Connected to MQTT broker at " << ADDRESS << std::endl;
    return 0;
}

int MQTTFunctions::subscribe_topic(const std::string& topic) {
    int rc = MQTTClient_subscribe(_client, topic.c_str(), QOS);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Failed to subscribe to topic \"" << topic << "\", return code " << rc << std::endl;
        return -1;
    }
    std::cout << "Subscribed to the topic \"" << topic << "\"" << std::endl;
    return 0;
}

int MQTTFunctions::unsubscribe_topic(const std::string& topic) {
    int rc = MQTTClient_unsubscribe(_client, topic.c_str());
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Failed to unsubscribe from topic \"" << topic << "\", return code " << rc << std::endl;
        return -1;
    }
    std::cout << "Unsubscribed from the topic \"" << topic << "\"" << std::endl;
    return 0;
}

int MQTTFunctions::publish_message(std::string& topic, std::string& message) {
    if (!_client || !MQTTClient_isConnected(_client)) {
        std::cerr << "MQTT client not initialized or disconnected." << std::endl;
        return -1;
    }
   // subscribe_topic(topic);
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = (void*)message.c_str();
    pubmsg.payloadlen = message.length();
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    int rc = MQTTClient_publishMessage(_client, topic.c_str(), &pubmsg, &token);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Failed to publish message to topic \"" << topic << "\", return code " << rc << std::endl;
        return -1;
    }
    MQTTClient_waitForCompletion(_client, token, TIMEOUT);
   // std::cout << "Message delivered with delivery token " << token << std::endl;
   // unsubscribe_topic(topic);
    return 0;
}

int MQTTFunctions::messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message) {
    std::string msg((char*)message->payload, message->payloadlen);
    std::cout << "Message arrived on topic \"" << topicName << "\": " << msg << std::endl;
    Communicator::messageArrived(msg);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

int MQTTFunctions::disconnect_mqtt_client() {
    if (!_client) {
        std::cerr << "MQTT client not initialized." << std::endl;
        return -1;
    }
    int rc = MQTTClient_disconnect(_client, 10000);
    if (rc != MQTTCLIENT_SUCCESS) {
        std::cerr << "Failed to disconnect from MQTT broker, return code " << rc << std::endl;
        return -1;
    }
    MQTTClient_destroy(&_client);
    std::cout << "Disconnected from MQTT broker." << std::endl;
    return 0;
}

