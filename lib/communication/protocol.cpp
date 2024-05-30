#include "protocol.h"
#include <thread>
#include <chrono>
#include <iostream>

const std::string SERVER_ADDRESS = "tcp://mqtt.eclipseprojects.io:1883";
std::string Protocol::clientId;
MQTTAsync Protocol::client = nullptr;
bool Protocol::isConnected = false;
bool Protocol::isSubscribedToClientId = false;
bool Protocol::isSubscribedToBroadcast = false;

void Protocol::connlost(void *context, char *cause) {
    std::cout << "Connection lost: " << cause << std::endl;
    isConnected = false;
    isSubscribedToClientId = false;
    isSubscribedToBroadcast = false;
}

int Protocol::msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message) {
    std::string msg((char*)message->payload, message->payloadlen);
    std::cout << "Message arrived on topic " << topicName << ": " << msg << std::endl;
    Communicator::messageArrived(msg);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

void Protocol::onConnectFailure(void* context, MQTTAsync_failureData* response) {
    std::cout << "Connection failed, rc " << (response ? response->code : 0) << std::endl;
    isConnected = false;
}

void Protocol::onConnectSuccess(void* context, MQTTAsync_successData* response) {
    std::cout << "Successfully connected" << std::endl;
    isConnected = true;

    // Subscribe to the clientId and broadcast topics
    subscribe(clientId);
    subscribe("broadcast");
}

void Protocol::onSubscribeSuccess(void* context, MQTTAsync_successData* response) {
    SubscribeContext* subscribeContext = static_cast<SubscribeContext*>(context);
    std::cout << "Subscribed successfully to topic: " << subscribeContext->topic << std::endl;
    if (subscribeContext->topic == subscribeContext->clientId) {
        isSubscribedToClientId = true;
    } else if (subscribeContext->topic == "broadcast") {
        isSubscribedToBroadcast = true;
    }
    delete subscribeContext;  // Liberar memória alocada
}

void Protocol::onSubscribeFailure(void* context, MQTTAsync_failureData* response) {
    SubscribeContext* subscribeContext = static_cast<SubscribeContext*>(context);
    std::cout << "Subscribe failed for topic: " << subscribeContext->topic << ", rc " << (response ? response->code : 0) << std::endl;
    delete subscribeContext;  // Liberar memória alocada
}

void Protocol::initialize(const std::string& id) {
    clientId = id;
    MQTTAsync_create(&client, SERVER_ADDRESS.c_str(), clientId.c_str(), MQTTCLIENT_PERSISTENCE_NONE, nullptr);

    MQTTAsync_setCallbacks(client, nullptr, connlost, msgarrvd, nullptr);

    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = onConnectSuccess;
    conn_opts.onFailure = onConnectFailure;
    conn_opts.context = nullptr;

    int rc;
    if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS) {
        std::cout << "Failed to start connect, return code " << rc << std::endl;
        exit(EXIT_FAILURE);
    }

    // Aguarde a conexão ser estabelecida
    while (!isConnected) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Aguarde até que as inscrições estejam concluídas
    while (!isSubscribedToClientId || !isSubscribedToBroadcast) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool Protocol::send(const std::string& destination, const std::string& message) {
    if (!isConnected) {
        std::cout << "Not connected, unable to send message" << std::endl;
        return false;
    }

    std::cout << "Sending message to topic " << destination << ": " << message << std::endl;

    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
    pubmsg.payload = (void*)message.c_str();
    pubmsg.payloadlen = message.length();
    pubmsg.qos = 1;
    pubmsg.retained = 0;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    opts.onSuccess = [](void* context, MQTTAsync_successData* response) {
        std::cout << "Message delivered successfully" << std::endl;
    };
    opts.onFailure = [](void* context, MQTTAsync_failureData* response) {
        std::cout << "Message delivery failed, rc " << (response ? response->code : 0) << std::endl;
    };

    int rc;
    if ((rc = MQTTAsync_sendMessage(client, destination.c_str(), &pubmsg, &opts)) != MQTTASYNC_SUCCESS) {
        std::cout << "Failed to start sendMessage, return code " << rc << std::endl;
        return false;
    }
    return true;
}

void Protocol::subscribe(const std::string& topic) {
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    SubscribeContext* context = new SubscribeContext{topic, clientId};  // Alocar contexto para o callback
    opts.onSuccess = onSubscribeSuccess;
    opts.onFailure = onSubscribeFailure;
    opts.context = context;

    int rc;
    if ((rc = MQTTAsync_subscribe(client, topic.c_str(), 1, &opts)) != MQTTASYNC_SUCCESS) {
        std::cout << "Failed to start subscribe, return code " << rc << std::endl;
        delete context;  // Liberar memória alocada em caso de falha
    }
}

int Protocol::disconnect() {
    MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
    opts.onSuccess = [](void* context, MQTTAsync_successData* response) {
        std::cout << "Successfully disconnected" << std::endl;
    };
    opts.onFailure = [](void* context, MQTTAsync_failureData* response) {
        std::cout << "Disconnect failed, rc " << (response ? response->code : 0) << std::endl;
    };

    int rc;
    if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS) {
        std::cout << "Failed to start disconnect, return code " << rc << std::endl;
        return rc;
    }
    MQTTAsync_destroy(&client);
    return MQTTASYNC_SUCCESS;
}

