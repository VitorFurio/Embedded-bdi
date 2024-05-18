#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>

bool action_say_start()
{
  std::cout << "Hey, I'm Alice and I'm running..." << std::endl;
  return true;
}


bool action_say_hello()
{
  std::cout << "Hello Bob, I'm Alice!" << std::endl;
  std::cout << "Is it day or night now?" << std::endl;
  return true;
}

bool action_say_its_day()
{
  std::cout << "Ohh, it's day, I'm going for a walk in the park!" << std::endl;
  return true;
}

bool action_say_its_night()
{
  std::cout << "Meh, it's night, I'm going to sleep..." << std::endl;
  return true;
}

#endif /* FUNCTIONS_H_ */
