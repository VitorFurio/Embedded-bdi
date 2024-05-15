#ifndef MSG_LIST_H
#define MSG_LIST_H

#include <iostream>
#include <string>
#include "../syntax/cenumfor_ilf.h"
#include "../syntax/proposition.h"

// Estrutura para armazenar os dados do item
struct Item_list {
    std::string name; // Nome da propriedade
    Proposition prop; // Objeto Proposition substituindo 'number'
    bool status; // true se recebeu uma mensagem
    CENUMFOR_ILF ilf;
    Item_list* next;

    // Construtor para inicializar os membros
    Item_list(const std::string& itemName, Proposition itemProp, bool itemStatus, CENUMFOR_ILF ilf);
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
    void addItem(const std::string& name, uint8_t propNumber, bool status);  

    Item_list* searchByName(const std::string& name);
    bool getStatusByName(const std::string& name);
    void setStatusByName(const std::string& name, bool newStatus);

    // Função para buscar um item pela Proposition
    Item_list* searchByProposition(Proposition prop);

    // Função para definir o status de um item pela Proposition
    void setStatusByProposition(Proposition prop, bool newStatus);

    // Função para obter o status de um item pela Proposition
    bool getStatusByProposition(Proposition prop);

    // Função para obter o tamanho da lista
    int getSize();

    Item_list* getHead();

    void print();
};

#endif // MSG_LIST_H

