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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Communicator {
private:
    static MsgList* _list;
    static std::string _name;
     
public:
    Communicator();
    Communicator(MsgList* list);
    static void initializeClient();
    void update(BeliefBase * belief_base, EventBase * event_base);
    static int messageArrived(const std::string& msg);
    static int publish_message(std::string& topic, std::string& message);
    static bool internal_action_broadcast();
    static bool internal_action_send();
    static bool internal_action_my_name();
    static void setName(const std::string name); 
    ~Communicator();
};

#endif // COMMUNICATOR_H

