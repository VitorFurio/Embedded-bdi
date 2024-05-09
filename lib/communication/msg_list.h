#ifndef MSG_LIST_H
#define MSG_LIST_H

#include <iostream>
#include <string>
#include <cstdint>
#include "../syntax/cenumfor_ilf.h"

// Estrutura para armazenar os dados do item
struct Item_list {
    std::string name;
    uint8_t number;
    bool status;
    CENUMFOR_ILF _ilf;
    Item_list* next;

    // Construtor para inicializar os membros
    Item_list(const std::string& itemName, uint8_t itemNumber, bool itemStatus, CENUMFOR_ILF _ilf);
};

class MsgList {
private:
    Item_list* head; // Ponteiro para o início da lista
    int size;   // Tamanho da lista

public:
    // Construtor padrão para inicializar a lista vazia
    MsgList();

    // Destrutor para liberar a memória alocada
    ~MsgList();

    // Função para inserir um novo item na lista
    void addItem(const std::string& name, uint8_t number, bool status);

    // Função para buscar um item pelo nome
    Item_list* searchByName(const std::string& name);

    // Função para buscar um item pelo número
    Item_list* searchByNumber(uint8_t number);

    // Função para definir o status de um item pelo nome
    void setStatusByName(const std::string& name, bool newStatus);

    // Função para definir o status de um item pelo número
    void setStatusByNumber(uint8_t number, bool newStatus);

    // Função para obter o status de um item pelo nome
    bool getStatusByName(const std::string& name);

    // Função para obter o status de um item pelo número
    bool getStatusByNumber(uint8_t number);

    // Função para obter o tamanho da lista
    int getSize();
    void print();
};



#endif // MSG_LIST_H