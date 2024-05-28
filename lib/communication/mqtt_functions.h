#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H

#include "communicator.h"

#define ADDRESS     "mqtt://mqtt.eclipseprojects.io"
#define CLIENTID    "AgentSender"
#define QOS         1
#define TIMEOUT     10000L

class MQTTFunctions {
public:
    // Initializes the MQTT client and connects to the broker.
    static void initializeClient(const std::string& topic);

    // Setup the MQTT client with the necessary callbacks and configurations.
    static int setup_mqtt_client();

    // Subscribe to a given topic.
    static int subscribe_topic(const std::string& topic);

    // Publish a message to a specific topic.
    static int publish_message(const std::string& topic, const std::string& message);

    // Callback function to handle messages that arrive at subscribed topics.
    static int messageArrived();

    // Disconnect and clean up the MQTT client.
    static int disconnect_mqtt_client();

private:
   
};

#endif // MQTT_FUNCTIONS_H
