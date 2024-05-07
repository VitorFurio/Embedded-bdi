#include "mqtt_functions.h"

// Callback chamada quando uma mensagem é recebida
int messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    printf("Message arrived on topic \"%s\": %.*s\n", topicName, message->payloadlen, (char *)message->payload);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

// Setup inicial: criação do cliente MQTT e conexão ao broker MQTT
int setup_mqtt_client(MQTTClient *client) {
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    MQTTClient_create(client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_setCallbacks(*client, NULL, NULL, messageArrived, NULL)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to set callbacks, return code %d\n", rc);
        return -1;
    }

    if ((rc = MQTTClient_connect(*client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        return -1;
    }

    printf("Connected to %s\n", ADDRESS);

    return 0;
}

// Funcionalidade: inscrição em um tópico MQTT
//int subscribe_topic(MQTTClient client, const char *topic) {
//    int rc;

 //   if ((rc = MQTTClient_subscribe(client, topic, QOS)) != MQTTCLIENT_SUCCESS) {
 //       printf("Failed to subscribe to topic \"%s\", return code %d\n", topic, rc);
  //      return -1;
 //   }

  //  printf("Subscribed to topic \"%s\"\n", topic);
  //  return 0;
//}

int subscribe_topic(MQTTClient *client_ptr, const char *topic) {
    int rc;

    if ((rc = MQTTClient_subscribe(*client_ptr, topic, QOS)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to subscribe to topic \"%s\", return code %d\n", topic, rc);
        return -1;
    }

    printf("Subscribed to topic \"%s\"\n", topic);
    return 0;
}

// Funcionalidade: publicação de uma mensagem em um tópico MQTT
int publish_message(MQTTClient client, const char *topic, const char *message) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    pubmsg.payload = (void *)message;
    pubmsg.payloadlen = strlen(message);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;

    if ((rc = MQTTClient_publishMessage(client, topic, &pubmsg, &token)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to publish message to topic \"%s\", return code %d\n", topic, rc);
        return -1;
    }

    printf("Waiting for publication of \"%s\" on topic \"%s\"\n", message, topic);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);

    return rc;
}

int disconnect_mqtt_client(MQTTClient client) {
    int rc;
    if ((rc = MQTTClient_disconnect(client, 10000)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to disconnect from MQTT broker, return code %d\n", rc);
        return -1;
    }
    MQTTClient_destroy(&client);
    printf("Disconnected from MQTT broker\n");
    return 0;
}
