#include "communicator.h"
#include <iostream>
#include <sstream>
#include <string>

MsgList* Communicator::_list = nullptr;
std::string Communicator::_name = "None"; 

Communicator::Communicator(){}
Communicator::Communicator(MsgList* list) : Communicator() {
    if (list) {
        _list = list;
    } else {
        std::cerr << "Error: Null pointer provided for MsgList." << std::endl;
    }
}
Communicator::~Communicator() {}

void Communicator::initializeClient() {
    MQTTFunctions::initializeClient(_name);
}

// Auxiliary functions
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

void Communicator::update(BeliefBase* belief_base, EventBase* event_base) {
    if (!_list || !belief_base || !event_base) {
        std::cerr << "Error: Null pointer provided to update method." << std::endl;
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
                    std::cerr << "Error: Unknown ILF received. Name: " << current->name << std::endl;
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
                std::cerr << "Error: Proposition <" << msg_prop << "> does not exist in the agent's base." << std::endl;
            }
        } else {
            std::cerr << "Error: ILF <" << msg_ilf << "> is not valid." << std::endl;
        }
    } else {
        std::cerr << "Error: Invalid message format. Expected 'ILF/prop'." << std::endl;
    }
    return 1;
}

int Communicator::publish_message(std::string& topic, std::string& message) {
    return MQTTFunctions::publish_message(topic, message);
}

bool Communicator::internal_action_broadcast() {
    if (!_list) {
        std::cerr << "Error: MsgList not initialized." << std::endl;
        return false;
    }
    auto item = _list->searchByProposition(Sender::getProp());
    if (!item) {
        std::cerr << "Error: No item found for the provided proposition." << std::endl;
        return false;
    }
    std::string topic = "broadcast"; 
    std::string message = IlfToString(Sender::getIlf()) + "/" + item->name;
    publish_message(topic, message);
    return true;
}

bool Communicator::internal_action_send() {
    if (!_list) {
        std::cerr << "Error: MsgList not initialized." << std::endl;
        return false;
    }
    auto item = _list->searchByProposition(Sender::getProp());
    if (!item) {
        std::cerr << "Error: No item found for the provided proposition." << std::endl;
        return false;
    }
    std::string topic = Sender::getDest();  
    std::string message = IlfToString(Sender::getIlf()) + "/" + item->name;
    MQTTFunctions::subscribe_topic(topic);
    publish_message(topic, message);
    MQTTFunctions::unsubscribe_topic(topic);
    return true;
}

void Communicator::setName(const std::string name) {
    _name = name;
}

bool Communicator::internal_action_my_name() {
     std::cerr << "Nome do agente: " << _name << std::endl;
    return true;
}