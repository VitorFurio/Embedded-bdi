#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>

bool action_say_start()
{
  std::cout << std::endl << "Hey, I'm Alice and I'm running..." << std::endl << std::endl;
  return true;
}


bool action_say_hello()
{
  std::cout << std::endl << "Hello Everyone, I'm Alice!" << std::endl;
  std::cout << "[Question to Bob] Is it day or night now?" << std::endl;
  return true;
}

bool action_say_its_day()
{
  std::cout  << std::endl<< "Ohh, it's day, I'm going for a walk in the park!" << std::endl;
  return true;
}

bool action_say_its_night()
{
  std::cout << std::endl << "Meh, it's night, I'm going to sleep..." << std::endl;
  return true;
}

#endif /* FUNCTIONS_H_ */
