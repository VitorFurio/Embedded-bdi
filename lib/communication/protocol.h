#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "communicator.h"
#include <stdio.h>
#include <string.h>
#include <MQTTAsync.h>

class Protocol {
public:
    // Initializes the protocol (performs connection, authentication, etc.)
    static void initialize(const std::string& Id);

    // Send a message to a specific destination.
    static bool send(const std::string& destination, const std::string& message);

    // Subscribe to a specific topic.
    static void subscribe(const std::string& topic);

    // Disconnect and clean up the communicator protocol.
    static int disconnect();

private:
    static MQTTAsync client;
    static std::string clientId;
    static const std::string SERVER_ADDRESS;
};

#endif // PROTOCOL_H

