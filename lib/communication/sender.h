#ifndef SENDER_H
#define SENDER_H

#include <string>
#include "../syntax/cenumfor_ilf.h"
#include "../syntax/proposition.h"  

// Functions called by Embedded-bdi do not take arguments. 
// The static Sender class works as a bridge to send data from the body_instruction to the Internal Actions defined in Communicator.

class Sender {
private:
    static Proposition _prop;
    static std::string _dest;
    static CENUMFOR_ILF _ilf;

public:
    static void setProp(Proposition prop);
    static void setDest(const std::string& dest);
    static void setIlf(CENUMFOR_ILF ilf);

    static Proposition getProp();
    static std::string getDest();
    static CENUMFOR_ILF getIlf();
};

#endif // SENDER_H

