#include "msg_list.h"

// Implementação do construtor da estrutura Item
Item_list::Item_list(const std::string& itemName, uint8_t itemNumber, bool itemStatus, CENUMFOR_ILF ilf)
    : name(itemName), number(itemNumber), status(itemStatus), _ilf(ilf), next(nullptr) {}

// Implementação do construtor da classe MsgList
MsgList::MsgList() : head(nullptr), size(0) {}

// Implementação do destrutor da classe MsgList
MsgList::~MsgList() {
    while (head != nullptr) {
        Item_list* temp = head;
        head = head->next;
        delete temp;
    }
}

// Implementação da função para inserir um novo item na lista
void MsgList::addItem(const std::string& name, uint8_t number, bool status) {
    Item_list* newItem = new Item_list(name, number, status, CENUMFOR_ILF::TELL);
    newItem->next = head;
    head = newItem;
    ++size;
}

// Implementação da função para buscar um item pelo nome
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

// Implementação da função para buscar um item pelo número
Item_list* MsgList::searchByNumber(uint8_t number) {
    Item_list* current = head;
    while (current != nullptr) {
        if (current->number == number) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Implementação da função para definir o status de um item pelo nome
void MsgList::setStatusByName(const std::string& name, bool newStatus) {
    Item_list* itemToUpdate = searchByName(name);
    if (itemToUpdate != nullptr) {
        itemToUpdate->status = newStatus;
    } else {
        std::cout << "Item '" << name << "' não encontrado." << std::endl;
    }
}

// Implementação da função para definir o status de um item pelo número
void MsgList::setStatusByNumber(uint8_t number, bool newStatus) {
    Item_list* itemToUpdate = searchByNumber(number);
    if (itemToUpdate != nullptr) {
        itemToUpdate->status = newStatus;
    } else {
        std::cout << "Item com número '" << static_cast<int>(number) << "' não encontrado." << std::endl;
    }
}

// Implementação da função para obter o status de um item pelo nome
bool MsgList::getStatusByName(const std::string& name) {
    Item_list* item = searchByName(name);
    if (item != nullptr) {
        return item->status;
    } else {
        std::cout << "Item '" << name << "' não encontrado." << std::endl;
        return false;
    }
}

// Implementação da função para obter o status de um item pelo número
bool MsgList::getStatusByNumber(uint8_t number) {
    Item_list* item = searchByNumber(number);
    if (item != nullptr) {
        return item->status;
    } else {
        std::cout << "Item com número '" << static_cast<int>(number) << "' não encontrado." << std::endl;
        return false;
    }
}

// Implementação da função para obter o tamanho da lista
int MsgList::getSize() {
    return size;
}

void MsgList::print() {
    Item_list* current = head;
    std::cout << "Lista de Itens:" << std::endl;
    while (current != nullptr) {
        std::cout << "- Número: " << static_cast<int>(current->number) << ", Status: " << current->status << ", ILF: " << static_cast<int>(current->_ilf) << ", Nome: " << current->name << std::endl;
        current = current->next;
    }
    std::cout << std::endl;
}
