#include "sender.h"

// Inicialização dos membros estáticos
Proposition Sender::_prop = Proposition(0);  // Inicializado com o valor padrão usando o construtor de Proposition
std::string Sender::_dest = "None";
CENUMFOR_ILF Sender::_ilf = CENUMFOR_ILF::TELL;

void Sender::setProp(Proposition prop) {
    _prop = prop;
}

void Sender::setDest(const std::string& dest) {
    _dest = dest;
}

void Sender::setIlf(CENUMFOR_ILF ilf) {
    _ilf = ilf;
}

Proposition Sender::getProp() {
    return _prop;
}

std::string Sender::getDest() {
    return _dest;
}

CENUMFOR_ILF Sender::getIlf() {
    return _ilf;
}

