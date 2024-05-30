#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "communicator.h"
#include <stdio.h>
#include <string.h>

// This class implements the chosen communication protocol for agents.

class Protocol {
public:
    // Initializes the protocol (performs connection, authentication, etc.)
    static void initialize(const std::string& Id);

    // Send a message to a specific destination.
    static bool send(const std::string& destination, const std::string& message);

    // Callback function to handle messages arriving at the agent.
    static int messageArrived();

    // Disconnect and clean up the communicator protocol.
    static int disconnect();

private:

};

#endif // PROTOCOL_H
