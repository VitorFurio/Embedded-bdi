#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>

bool action_say_hello()
{
  std::cout << "Hello, I'm Bob!!" << std::endl;
  return true;
}


bool update_hello()
{
  std::cout << "Hello world!" << std::endl;
  std::cout << "I am an agent and I will keep running until " <<
               "I am terminated" << std::endl;
  return true;
}

#endif /* FUNCTIONS_H_ */
