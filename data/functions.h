#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>

bool action_say_hello()
{
  std::cout << "Hello world!" << std::endl;
  std::cout << "I am an agent and I will keep running until " <<
               "I am terminated" << std::endl;
  return true;
}

bool action_say_test()
{
  std::cout << "Saying test..." << std::endl;
  return true;
}

bool internal_action_broadcast_externo()
{
  std::cout << "Recebendo do broadcast:" << std::endl;
 // std::cout << "param 1: " << str1 << std::endl;
 // std::cout << "param 2: " << str2 << std::endl;
  return true;
}

bool update_hello()
{
  std::cout << "Hello world!" << std::endl;
  std::cout << "I am an agent and I will keep running until " <<
               "I am terminated" << std::endl;
  return true;
}

bool update_teste()
{
  std::cout << "Função da Belief teste" << std::endl;
  return true;
}

//bool internal_action_broadcast(const std::string& msg)
//bool internal_action_broadcast()
//{
//  std::cout << "Recebendo do broadcast:" << std::endl;
  //std::cout << "param 1: " << msg << std::endl;
//  return true;
//}

#endif /* FUNCTIONS_H_ */
