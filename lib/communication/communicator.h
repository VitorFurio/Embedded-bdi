#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "msg_list.h"
#include "sender.h"
#include "protocol.h"

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
    // Constructors and destructors
    Communicator();
    Communicator(MsgList* list);
    ~Communicator();

    // Communication functions
    static void initialize();
    static void setName(const std::string name); 
    void update(BeliefBase * belief_base, EventBase * event_base);
    static int messageArrived(const std::string& msg);
    static bool send(std::string& destintion, std::string& message);
    
    // Internal Actions
    static bool internal_action_broadcast();
    static bool internal_action_send();
    static bool internal_action_my_name();
};

#endif // COMMUNICATOR_H

