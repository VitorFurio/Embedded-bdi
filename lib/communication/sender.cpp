// Sender.cpp
#include "sender.h"

// Inicialização dos membros estáticos
uint8_t Sender::_prop = 0;
std::string Sender::_dest = "InitialDest";
CENUMFOR_ILF Sender::_ilf = CENUMFOR_ILF::TELL; // Inicialização com o primeiro valor do enum

void Sender::setProp(uint8_t prop) {
    _prop = prop;
}

void Sender::setDest(const std::string& dest) {
    _dest = dest;
}

void Sender::setIlf(CENUMFOR_ILF ilf) {
    _ilf = ilf;
}

uint8_t Sender::getProp() {
    return _prop;
}

std::string Sender::getDest() {
    return _dest;
}

CENUMFOR_ILF Sender::getIlf() {
    return _ilf;
}

