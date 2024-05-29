#ifndef MSG_LIST_H
#define MSG_LIST_H

#include "../syntax/cenumfor_ilf.h"
#include "../syntax/proposition.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This object is a list of all the agent's propositions. 
// When a proposition is received via message, the Communicator::messageArrieve function updates this object. 
// The Communicator::update uses this object to add beliefs and events to the agent's mind.

// Structure to store an agent proposition.
struct Item_list {
    std::string name;   // Proposition as string
    Proposition prop;   // proposition as number
    int status;         // True if the agent received this proposition in a message
    CENUMFOR_ILF ilf;   // ILF of the received proposition
    Item_list* next;

    Item_list(const std::string& itemName, Proposition itemProp, int itemStatus, CENUMFOR_ILF ilf);
};

class MsgList {
private:
    Item_list* head; 
    int size; 

public:
    // Constructors and destructors
    MsgList();
    ~MsgList();

    //List functions
    void addItem(const std::string& name, uint8_t propNumber, int status);  

    Item_list* searchByName(const std::string& name);
    int getStatusByName(const std::string& name);
    void setStatusByName(const std::string& name, int newStatus);

    Item_list* searchByProposition(Proposition prop);
    int getStatusByProposition(Proposition prop);
    void setStatusByProposition(Proposition prop, int newStatus);
    
    int getSize();
    Item_list* getHead();
    void print();
};

#endif // MSG_LIST_H

