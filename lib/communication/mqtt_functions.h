#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H

#include "MQTTClient.h"
#include "communicator.h"
#include <string>
#include <iostream>

#define ADDRESS     "mqtt://mqtt.eclipseprojects.io"
#define CLIENTID    "Agent"
#define QOS         1
#define TIMEOUT     10000L

class MQTTFunctions {
public:
    // Initializes the MQTT client and connects to the broker.
    static void initializeClient(std::string& clientId);

    // Setup the MQTT client with the necessary callbacks and configurations.
    static int setup_mqtt_client(MQTTClient* client, std::string& clientId);

    // Subscribe to a given topic.
    static int subscribe_topic(const std::string& topic);
    static int unsubscribe_topic(const std::string& topic);

    // Publish a message to a specific topic.
    static int publish_message(std::string& topic, std::string& message);

    // Callback function to handle messages that arrive at subscribed topics.
    static int messageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message);

    // Disconnect and clean up the MQTT client.
    static int disconnect_mqtt_client();

private:
    // Static member to hold the MQTT client instance.
    static MQTTClient _client;
};

#endif // MQTT_FUNCTIONS_H
