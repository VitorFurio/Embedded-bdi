#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <iostream>
#include <string>
//#include <time.h>

time_t start = time(NULL);
bool fire = false;

bool action_trigger_alarm()
{
  std::cout   << "# ALERT! DANGEROUS CONDITION!! " << std::endl << std::endl;
  return true;
}

bool action_print_init()
{
  std::cout   << "Sensor1 iniciado." << std::endl << std::endl;
  
  return true;
}


bool action_print_alert()
{
  std::cout  << "Sensor1 operando em modo alerta." << std::endl << std::endl;
  return true;
}

bool action_print_default()
{
  std::cout  << "Sensor1 operando em modo normal." << std::endl << std::endl;
  return true;
}

bool action_print_fire()
{
  std::cout  << "# Fogo detectado!." << std::endl;
  return true;
}

bool action_print_not_fire()
{
  std::cout  << "# Sem Fogo!."  << std::endl;
  return true;
}

bool update_fire(bool var)
{
  return var;
}

#endif /* FUNCTIONS_H_ */
