/*
 * body_instruction.cpp
 *
 *  Created on: Jul 24, 2020
 *      Author: Matuzalem Muller
 */
#include <iostream>
#include "body_instruction.h"

BodyInstruction::BodyInstruction(BodyType type,
                                 Proposition prop,
                                 bool (*take_action)()) : _arg("hello")
{
  _type = type;
  _proposition = prop;
  _take_action = take_action;
  _operator = EventOperator::BELIEF_ADDITION;
  
  //_belief = nullptr;
}

BodyInstruction::BodyInstruction(BodyType type,
                                 Proposition prop,
                                 EventOperator event_operator) : _arg("hello")
{
  _type = type;
  _proposition = prop;
  _take_action = nullptr;
  _operator = event_operator;

  std::cout << _arg << "\n" << _arg2 << "\n";
  
  //_belief = nullptr;
}

// For internal action:
//BodyInstruction::BodyInstruction(BodyType type,
//                                 Proposition prop,
//                                 bool (*take_internal_action)(const std::string&))
//{
//  _type = type;
//  _proposition = prop;
//  _take_internal_action = take_internal_action;
// _operator = EventOperator::BELIEF_ADDITION;
//}

// Add handling of belief that is not in beliefbase
BodyReturn BodyInstruction::run_instruction(BeliefBase * belief_base,
                                            EventBase * event_base)
{
  BodyReturn result;
  Event event(_operator, _proposition);

  if (_type == BodyType::ACTION)
  {
    bool value = _take_action();
    result = BodyReturn(BodyType::ACTION, value, nullptr);
  }
  
  // For internal Action
  else if (_type == BodyType::INTERNAL_ACTION)
  {
    bool value = _take_action();
    result = BodyReturn(BodyType::ACTION, value, nullptr);
  }
  
  else if (_type == BodyType::BELIEF)
  {
    if (event_base->add_event(event))
    {
      if (_operator == EventOperator::BELIEF_ADDITION)
      {
        belief_base->change_belief_state(_proposition, true);
      }
      else
      {
        belief_base->change_belief_state(_proposition, false);
      }
      result = BodyReturn(BodyType::BELIEF,
                          true,
                          event_base->last_event()->get_event_id()
                          );
    }
    else
    {
      result = BodyReturn(BodyType::BELIEF, false, nullptr);
    }
  }
  else
  {
    if (event.get_operator() == EventOperator::GOAL_ACHIEVE)
    {
      event_base->add_event(event);
      result = BodyReturn(
                          BodyType::GOAL,
                          true,
                          nullptr
                          );
    }
    else if (event_base->add_event(event))
    {
      result = BodyReturn(
                          BodyType::GOAL,
                          true,
                          event_base->last_event()->get_event_id()
                          );
    }
    else
    {
      result = BodyReturn(BodyType::GOAL, false, nullptr);
    }
  }

  return result;
}


// For internal actions:
void BodyInstruction::add_arg(CENUMFOR_ILF ilf){
   _ilf = ilf;
}

//void BodyInstruction::add_arg(Belief belief){
 //  _belief = belief;
//}




