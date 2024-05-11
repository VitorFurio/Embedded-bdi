/*
 * cenumfor_ilf.h
 *
 *  Created on: Jul 5, 2020
 *      Author: Matuzalem Muller
 */

#ifndef SYNTAX_CENUMFOR_ILF_H_
#define SYNTAX_CENUMFOR_ILF_H_

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

#endif /* SYNTAX_CENUMFOR_ILF_H_ */
