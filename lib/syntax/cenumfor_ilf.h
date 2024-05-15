/*
 * cenumfor_ilf.h
 *
 *  Created on: Jul 5, 2020
 *      Author: Matuzalem Muller
 */

#ifndef SYNTAX_CENUMFOR_ILF_H_
#define SYNTAX_CENUMFOR_ILF_H_

#include <string>  // Inclui string para o uso de std::string

/**
 * Represents type of body instructions: Action, Goal or Belief operation.
 */
enum class CENUMFOR_ILF : unsigned char
{
  TELL,
  UNTELL,
  ACHIEVE,
  UNACHIEVE
};

inline std::string IlfToString(CENUMFOR_ILF ilf) {
    switch (ilf) {
        case CENUMFOR_ILF::TELL: return "TELL";
        case CENUMFOR_ILF::UNTELL: return "UNTELL";
        case CENUMFOR_ILF::ACHIEVE: return "ACHIEVE";
        case CENUMFOR_ILF::UNACHIEVE: return "UNACHIEVE";
        default: return "Unknown";
    }
}

#endif /* SYNTAX_CENUMFOR_ILF_H_ */

