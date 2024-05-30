#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>

bool action_say_hello()
{
  std::cout << "Hello, I'm Bob!!" << std::endl;
  return true;
}

bool action_say_night()
{
  std::cout << "It's night now, Alice." << std::endl;
  return true;
}

#endif /* FUNCTIONS_H_ */
