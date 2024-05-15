#include "msg_list.h"

// Implementação do construtor da estrutura Item
Item_list::Item_list(const std::string& itemName, Proposition itemProp, bool itemStatus, CENUMFOR_ILF ilf)
    : name(itemName), prop(itemProp), status(itemStatus), ilf(ilf), next(nullptr) {}

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
void MsgList::addItem(const std::string& name, uint8_t propNumber, bool status) {
    Proposition prop(propNumber);  // Cria uma instância de Proposition usando o número fornecido
    Item_list* newItem = new Item_list(name, prop, status, CENUMFOR_ILF::TELL);
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

// Implementação da função para definir o status de um item pelo nome
void MsgList::setStatusByName(const std::string& name, bool newStatus) {
    Item_list* itemToUpdate = searchByName(name);
    if (itemToUpdate != nullptr) {
        itemToUpdate->status = newStatus;
    } else {
        std::cout << "Item '" << name << "' não encontrado." << std::endl;
    }
}

// Implementação da função para buscar um item pela Proposition
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

// Implementação da função para definir o status de um item pela Proposition
void MsgList::setStatusByProposition(Proposition prop, bool newStatus) {
    Item_list* itemToUpdate = searchByProposition(prop);
    if (itemToUpdate != nullptr) {
        itemToUpdate->status = newStatus;
    } else {
        std::cout << "Proposition não encontrada." << std::endl;
    }
}

// Implementação da função para obter o status de um item pela Proposition
bool MsgList::getStatusByProposition(Proposition prop) {
    Item_list* item = searchByProposition(prop);
    if (item != nullptr) {
        return item->status;
    } else {
        std::cout << "Proposition não encontrada." << std::endl;
        return false;
    }
}

// Implementação da função para obter o tamanho da lista
int MsgList::getSize() {
    return size;
}

Item_list* MsgList::getHead() {
    return head;
}

void MsgList::print() {
    Item_list* current = head;
    std::cout << "Lista de Itens:" << std::endl;
    while (current != nullptr) {
        std::cout << "- Proposition: " << static_cast<int>(current->prop.get_name()) << ", Status: " << current->status << ", ILF: " << static_cast<int>(current->ilf) << ", Nome: " << current->name << std::endl;
        current = current->next;
    }
    std::cout << std::endl;
}

