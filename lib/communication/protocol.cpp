#include "protocol.h"

void Protocol::initialize(const std::string& Id) {
    printf("Implement initialization function with ID: %s.\n",Id.c_str());
}

int Protocol::send(const std::string& destination, const std::string& message) {
    printf("Implement send function to send %s to %s.\n",message.c_str(),destination.c_str());
    return 0;
}

int Protocol::messageArrived() {
    // Message arrived by the protocol in ILF/proposition format
    std::string message = "ILF/proposition";
    Communicator::messageArrived(message);
    return 1;
}

int Protocol::disconnect() {
    printf("Implement disconnect function.\n");
    return 0;
}

