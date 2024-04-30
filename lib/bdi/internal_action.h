/*
 * internal_action_functions.h
 *
 *  Created on: Abr 28, 2024
 *      Author: Vitor Fúrio
 */

#ifndef SYNTAX_INTERNAL_ACTION_FUNCTIONS_H_
#define SYNTAX_INTERNAL_ACTION_FUNCTIONS_H_

#include <iostream>
#include <string>
#include "../syntax/cenumfor_ilf.h"

bool internal_action_broadcast()
{
  std::cout << "Recebendo do broadcast:" << std::endl;
  //std::cout << "param 1: " << msg << std::endl;
  return true;
}

bool internal_action_broadcast2(CENUMFOR_ILF ilf)
{
  std::cout << "Recebendo do broadcast:" << std::endl;
  std::cout << "Valor do enumerável: " << static_cast<int>(ilf) << std::endl;
  return true;
}

#endif /* SYNTAX_INTERNAL_ACTION_FUNCTIONS_H_ */
