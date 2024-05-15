#ifndef SENDER_H
#define SENDER_H

#include <string>
#include "../syntax/cenumfor_ilf.h"
#include "../syntax/proposition.h"  // Inclusão da classe Proposition

class Sender {
private:
    static Proposition _prop;  // Alterado de uint8_t para Proposition
    static std::string _dest;
    static CENUMFOR_ILF _ilf;

public:
    static void setProp(Proposition prop);  // Assinatura alterada para receber Proposition
    static void setDest(const std::string& dest);
    static void setIlf(CENUMFOR_ILF ilf);

    static Proposition getProp();  // Tipo de retorno alterado para Proposition
    static std::string getDest();
    static CENUMFOR_ILF getIlf();
};

#endif // SENDER_H

