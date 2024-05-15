// Em Communicator.h

#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "msg_list.h"
#include "sender.h"
#include "mqtt_functions.h"
#include "../bdi/belief.h"
#include "../bdi/belief_base.h"
#include "../bdi/event.h"
#include "../bdi/event_base.h"
#include "../syntax/cenumfor_ilf.h"
#include "../syntax/proposition.h"

#include "MQTTClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Communicator {
private:
    static MsgList* _list;
    static MQTTClient _client;
     
public:
    Communicator();
    Communicator(MsgList* list);
    static void initializeClient();
    void update(BeliefBase * belief_base, EventBase * event_base);
    static int publish_message(const char* topic, const std::string& message);
    static int messageArrived(const std::string& msg);
    static bool internal_action_broadcast();
    ~Communicator();
};

#endif // COMMUNICATOR_H

