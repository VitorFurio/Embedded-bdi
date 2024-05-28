#include "msg_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementação do construtor da estrutura Item
Item_list::Item_list(const std::string& itemName, Proposition itemProp, int itemStatus, CENUMFOR_ILF ilf)
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
void MsgList::addItem(const std::string& name, uint8_t propNumber, int status) {
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
int MsgList::getStatusByName(const std::string& name) {
    Item_list* item = searchByName(name);
    if (item != nullptr) {
        return item->status;
    } else {
        printf("Item '%s' não encontrado.\n", name.c_str());
        return 0;
    }
}

// Implementação da função para definir o status de um item pelo nome
void MsgList::setStatusByName(const std::string& name, int newStatus) {
    Item_list* itemToUpdate = searchByName(name);
    if (itemToUpdate != nullptr) {
        itemToUpdate->status = newStatus;
    } else {
        printf("Item '%s' não encontrado.\n", name.c_str());
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
void MsgList::setStatusByProposition(Proposition prop, int newStatus) {
    Item_list* itemToUpdate = searchByProposition(prop);
    if (itemToUpdate != nullptr) {
        itemToUpdate->status = newStatus;
    } else {
        printf("Proposition não encontrada.\n");
    }
}

// Implementação da função para obter o status de um item pela Proposition
int MsgList::getStatusByProposition(Proposition prop) {
    Item_list* item = searchByProposition(prop);
    if (item != nullptr) {
        return item->status;
    } else {
        printf("Proposition não encontrada.\n");
        return 0;
    }
}

// Implementação da função para obter o tamanho da lista
int MsgList::getSize() {
    return size;
}

Item_list* MsgList::getHead() {
    return head;
}

// Implementação da função para imprimir a lista
void MsgList::print() {
    Item_list* current = head;
    printf("Lista de Itens:\n");
    while (current != nullptr) {
        printf("- Proposition: %d, Status: %d, ILF: %s, Nome: %s\n", 
               current->prop.get_name(), current->status, IlfToString(current->ilf).c_str(), current->name.c_str());
        current = current->next;
    }
    printf("\n");
}

