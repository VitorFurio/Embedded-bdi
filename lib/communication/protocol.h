#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "communicator.h"
#include <string>
#include <MQTTAsync.h>

class Protocol {
public:
    // Initializes the protocol (performs connection, authentication, etc.)
    static void initialize(const std::string& id);

    // Send a message to a specific destination.
    static bool send(const std::string& destination, const std::string& message);

    // Subscribe to a specific topic.
    static void subscribe(const std::string& topic);

    // Disconnect and clean up the communicator protocol.
    static int disconnect();

private:
    static void connlost(void *context, char *cause);
    static int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message);
    static void onConnectFailure(void* context, MQTTAsync_failureData* response);
    static void onConnectSuccess(void* context, MQTTAsync_successData* response);
    static void onSubscribeSuccess(void* context, MQTTAsync_successData* response);
    static void onSubscribeFailure(void* context, MQTTAsync_failureData* response);

    static std::string clientId;
    static MQTTAsync client;
    static bool isConnected;
    static bool isSubscribedToClientId;
    static bool isSubscribedToBroadcast;

    struct SubscribeContext {
        std::string topic;
        std::string clientId;
    };
};

#endif // PROTOCOL_H

