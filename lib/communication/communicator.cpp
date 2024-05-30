 #include "communicator.h"

MsgList* Communicator::_list = nullptr;
std::string Communicator::_name = "None"; 

Communicator::Communicator(){}
Communicator::Communicator(MsgList* list) : Communicator() {
    if (list) {
        _list = list;
    } else {
        printf("Error: Null pointer provided for MsgList.\n");
    }
}
Communicator::~Communicator() {}

//--------------------- Auxiliary functions ---------------------
bool parseMessage(const std::string& message, std::string& ilf, std::string& prop) {
    size_t pos = message.find('/');
    if (pos == std::string::npos || pos == 0 || pos + 1 == message.length()) {
        return false;
    }
    ilf = message.substr(0, pos);
    prop = message.substr(pos + 1);
    return true;
}

std::pair<bool, CENUMFOR_ILF> stringToILF(const std::string& str) {
    if (str == "TELL") {
        return {true, CENUMFOR_ILF::TELL};
    } else if (str == "UNTELL") {
        return {true, CENUMFOR_ILF::UNTELL};
    } else if (str == "ACHIEVE") {
        return {true, CENUMFOR_ILF::ACHIEVE};
    } else if (str == "UNACHIEVE") {
        return {true, CENUMFOR_ILF::UNACHIEVE};
    } else {
        return {false, CENUMFOR_ILF::TELL};  // Default error case
    }
}
//  -------------------- // -------------------- // --------------------

void Communicator::initialize() {
    Protocol::initialize(_name);
}

void Communicator::setName(const std::string name) {
    _name = name;
}

void Communicator::update(BeliefBase* belief_base, EventBase* event_base) {
    if (!_list || !belief_base || !event_base) {
        printf("Error: Null pointer provided to update method.\n");
        return;
    }
    for (Item_list* current = _list->getHead(); current != nullptr; current = current->next) {
        if (current->status) {
            if (!event_base->is_full()) {
                Event event;
                Proposition prop = current->prop;
                switch (current->ilf) {
                case CENUMFOR_ILF::TELL:
                    event = Event(EventOperator::BELIEF_ADDITION, prop);
                    belief_base->change_belief_state(prop, true);
                    break;
                case CENUMFOR_ILF::UNTELL:
                    event = Event(EventOperator::BELIEF_DELETION, prop);
                    belief_base->change_belief_state(prop, false);
                    break;
                case CENUMFOR_ILF::ACHIEVE:
                    event = Event(EventOperator::GOAL_ADDITION, prop);
                    break;
                case CENUMFOR_ILF::UNACHIEVE:
                    event = Event(EventOperator::GOAL_DELETION, prop);
                    break;
                default:
                    printf("Error: Unknown ILF received. Name: %s\n", current->name.c_str());
                    continue;
                }
                event_base->add_event(event);
                current->status = false;
            }
        }
    }
}

int Communicator::messageArrived(const std::string& msg) {
    std::string msg_ilf, msg_prop;
    if (parseMessage(msg, msg_ilf, msg_prop)) {
        auto result = stringToILF(msg_ilf);
        if (result.first) {
            Item_list* item = _list->searchByName(msg_prop);
            if (item) {
                item->status = true;
                item->ilf = result.second;
            } else {
                printf("Error: Proposition <%s> does not exist in the agent's base.\n", msg_prop.c_str());
            }
        } else {
            printf("Error: ILF <%s> is not valid.\n", msg_ilf.c_str());
        }
    } else {
        printf("Error: Invalid message format. Expected 'ILF/prop'.\n");
    }
    return 1;
}

bool Communicator::send(std::string& destination, std::string& message) {
    return Protocol::send(destination, message);
}

bool Communicator::internal_action_broadcast() {
    // The broadcast function may vary depending on the protocol. 
    // In this example, it sends the message to the 'broadcast' destination.
    Sender::setDest("broadcast");
    return internal_action_send();
}

bool Communicator::internal_action_send() {
    if (!_list) {
        printf("Error: MsgList not initialized.\n");
        return false;
    }
    auto item = _list->searchByProposition(Sender::getProp());
    if (!item) {
        printf("Error: No item found for the provided proposition.\n");
        return false;
    }
    std::string dest = Sender::getDest();  
    std::string message = IlfToString(Sender::getIlf()) + "/" + item->name;
    send(dest, message);
    return true;
}

bool Communicator::internal_action_my_name() {
    printf("Agent's Name: %s\n", _name.c_str());
    return true;
}
