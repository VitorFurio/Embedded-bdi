#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H

#include "MQTTClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ADDRESS     "mqtt://mqtt.eclipseprojects.io"
#define CLIENTID    "AgentSender"
#define QOS         1
#define TIMEOUT     10000L

int setup_mqtt_client(MQTTClient *client);
//int subscribe_topic(MQTTClient client, const char *topic);
int subscribe_topic(MQTTClient *client_ptr, const char *topic);

int publish_message(MQTTClient client, const char *topic, const char *message);
int messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
int disconnect_mqtt_client(MQTTClient client);

#endif /* MQTT_FUNCTIONS_H */

