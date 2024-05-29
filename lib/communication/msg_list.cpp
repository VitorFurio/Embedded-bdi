#include "msg_list.h"

Item_list::Item_list(const std::string& itemName, Proposition itemProp, int itemStatus, CENUMFOR_ILF ilf)
    : name(itemName), prop(itemProp), status(itemStatus), ilf(ilf), next(nullptr) {}

MsgList::MsgList() : head(nullptr), size(0) {}

MsgList::~MsgList() {
    while (head != nullptr) {
        Item_list* temp = head;
        head = head->next;
        delete temp;
    }
}

void MsgList::addItem(const std::string& name, uint8_t propNumber, int status) {
    Proposition prop(propNumber);  
    Item_list* newItem = new Item_list(name, prop, status, CENUMFOR_ILF::TELL);
    newItem->next = head;
    head = newItem;
    ++size;
}

Item_list* MsgList::searchByName(const std::string& name) {
    Item_list* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int MsgList::getStatusByName(const std::string& name) {
    Item_list* item = searchByName(name);
    if (item != nullptr) {
        return item->status;
    } else {
        printf("Item '%s' não encontrado.\n", name.c_str());
        return 0;
    }
}

void MsgList::setStatusByName(const std::string& name, int newStatus) {
    Item_list* itemToUpdate = searchByName(name);
    if (itemToUpdate != nullptr) {
        itemToUpdate->status = newStatus;
    } else {
        printf("Item '%s' não encontrado.\n", name.c_str());
    }
}

Item_list* MsgList::searchByProposition(Proposition prop) {
    Item_list* current = head;
    while (current != nullptr) {
        if (current->prop.is_equal(prop)) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int MsgList::getStatusByProposition(Proposition prop) {
    Item_list* item = searchByProposition(prop);
    if (item != nullptr) {
        return item->status;
    } else {
        printf("Proposition não encontrada.\n");
        return 0;
    }
}

void MsgList::setStatusByProposition(Proposition prop, int newStatus) {
    Item_list* itemToUpdate = searchByProposition(prop);
    if (itemToUpdate != nullptr) {
        itemToUpdate->status = newStatus;
    } else {
        printf("Proposition não encontrada.\n");
    }
}

int MsgList::getSize() {
    return size;
}

Item_list* MsgList::getHead() {
    return head;
}

void MsgList::print() {
    Item_list* current = head;
    printf("Proposition List:\n");
    while (current != nullptr) {
        printf("- Proposition: %d, Status: %d, ILF: %s, Name: %s\n", 
               current->prop.get_name(), current->status, IlfToString(current->ilf).c_str(), current->name.c_str());
        current = current->next;
    }
    printf("\n");
}

