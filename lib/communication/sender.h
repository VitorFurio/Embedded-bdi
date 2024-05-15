// Sender.h
#ifndef SENDER_H
#define SENDER_H

#include <string>
#include <cstdint> 
#include "../syntax/cenumfor_ilf.h"

class Sender {
private:
    static uint8_t _prop;
    static std::string _dest;
    static CENUMFOR_ILF _ilf;

public:
    static void setProp(uint8_t prop);
    static void setDest(const std::string& dest);
    static void setIlf(CENUMFOR_ILF ilf);

    static uint8_t getProp();
    static std::string getDest();
    static CENUMFOR_ILF getIlf();
};

#endif // SENDER_H

