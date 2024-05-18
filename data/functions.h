#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>

bool action_say_hello()
{
  std::cout << "Hello, I'm Alice!!" << std::endl;
  return true;
}

bool action_say_its_day()
{
  std::cout << "Ohh, it's day, I'm going for a walk in the park!!" << std::endl;
  return true;
}

bool action_say_its_night()
{
  std::cout << "Ohh, it's night, I'm going to sleep..." << std::endl;
  return true;
}

#endif /* FUNCTIONS_H_ */
