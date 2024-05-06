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

bool internal_action_broadcast()
{
  std::cout << "Recebendo do broadcast:" << std::endl;
  //std::cout << "param 1: " << msg << std::endl;
  return true;
}

#endif /* SYNTAX_INTERNAL_ACTION_FUNCTIONS_H_ */
