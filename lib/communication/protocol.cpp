#include "protocol.h"
#include <thread>
#include <chrono>
#include <MQTTAsync.h>

const std::string Protocol::SERVER_ADDRESS = "tcp://mqtt.eclipseprojects.io:1883";
MQTTAsync Protocol::client = nullptr;
std::string Protocol::clientId;
bool isConnected = false;  // Variável para verificar se a conexão está estabelecida
bool isSubscribedToClientId = false;
bool isSubscribedToBroadcast = false;

struct SubscribeContext {
    std::string topic;
    std::string clientId;
};

void connlost(void *context, char *cause) {
    printf("Connection lost: %s\n", cause);
    isConnected = false;  // Atualizar estado de conexão
    isSubscribedToClientId = false;
    isSubscribedToBroadcast = false;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message) {
    std::string msg((char*)message->payload, message->payloadlen);
    printf("Message arrived on topic %s: %s\n", topicName, msg.c_str());
    Communicator::messageArrived(msg);
    MQTTAsync_freeMessage(&message);
    MQTTAsync_free(topicName);
    return 1;
}

void onConnectFailure(void* context, MQTTAsync_failureData* response) {
    printf("Connection failed, rc %d\n", response ? response->code : 0);
    isConnected = false;  // Atualizar estado de conexão
}

void onConnectSuccess(void* context, MQTTAsync_successData* response) {
    printf("Successfully connected\n");
    isConnected = true;  // Atualizar estado de conexão

    // Retrieve the clientId from the context and subscribe to the clientId and broadcast topics
    std::string clientId = static_cast<const char*>(context);
    Protocol::subscribe(clientId);
    Protocol::subscribe("broadcast");
}

void onSubscribeSuccess(void* context, MQTTAsync_successData* response) {
    SubscribeContext* subscribeContext = static_cast<SubscribeContext*>(context);
    printf("Subscribed successfully to topic: %s\n", subscribeContext->topic.c_str());
    if (subscribeContext->topic == subscribeContext->clientId) {
        isSubscribedToClientId = true;
    } else if (subscribeContext->topic == "broadcast") {
        isSubscribedToBroadcast = true;
    }
    delete subscribeContext;  // Liberar memória alocada
}

void onSubscribeFailure(void* context, MQTTAsync_failureData* response) {
    SubscribeContext* subscribeContext = static_cast<SubscribeContext*>(context);
    printf("Subscribe failed for topic: %s, rc %d\n", subscribeContext->topic.c_str(), response ? response->code : 0);
    delete subscribeContext;  // Liberar memória alocada
}

void Protocol::initialize(const std::string& Id) {
    clientId = Id;
    MQTTAsync_create(&client, SERVER_ADDRESS.c_str(), clientId.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL);

    MQTTAsync_setCallbacks(client, NULL, connlost, msgarrvd, NULL);

    MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.onSuccess = onConnectSuccess;
    conn_opts.onFailure = onConnectFailure;
    conn_opts.context = (void*)clientId.c_str();

    int rc;
    if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start connect, return code %d\n", rc);
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
        printf("Not connected, unable to send message\n");
        return false;
    }

    printf("Sending message to topic %s: %s\n", destination.c_str(), message.c_str());

    MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
    pubmsg.payload = (void*)message.c_str();
    pubmsg.payloadlen = message.length();
    pubmsg.qos = 1;
    pubmsg.retained = 0;
    MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
    opts.onSuccess = [](void* context, MQTTAsync_successData* response) {
      //  printf("Message delivered successfully\n");
    };
    opts.onFailure = [](void* context, MQTTAsync_failureData* response) {
        printf("Message delivery failed, rc %d\n", response ? response->code : 0);
    };

    int rc;
    if ((rc = MQTTAsync_sendMessage(client, destination.c_str(), &pubmsg, &opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start sendMessage, return code %d\n", rc);
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
        printf("Failed to start subscribe, return code %d\n", rc);
        delete context;  // Liberar memória alocada em caso de falha
    }
}

int Protocol::disconnect() {
    MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
    opts.onSuccess = [](void* context, MQTTAsync_successData* response) {
        printf("Successfully disconnected\n");
    };
    opts.onFailure = [](void* context, MQTTAsync_failureData* response) {
        printf("Disconnect failed, rc %d\n", response ? response->code : 0);
    };

    int rc;
    if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS) {
        printf("Failed to start disconnect, return code %d\n", rc);
        return rc;
    }
    MQTTAsync_destroy(&client);
    return MQTTASYNC_SUCCESS;
}

