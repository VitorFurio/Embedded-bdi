/*
 * instantiated_plan.cpp
 *
 *  Created on: Jul 12, 2020
 *      Author: Matuzalem Muller
 */

#include "instantiated_plan.h"

InstantiatedPlan::InstantiatedPlan() {}

InstantiatedPlan::InstantiatedPlan(Plan * plan, IntentionID id)
{
  _plan = plan;
  _id = &id;
}

InstantiatedPlan::~InstantiatedPlan() {}

BodyReturn InstantiatedPlan::run_plan(BeliefBase * beliefs, EventBase * events)
{
  BodyReturn result = _plan->run_body(_index, beliefs, events);
  _index++;
  return result;
}

bool InstantiatedPlan::is_finished()
{
  return (_index == _plan->get_body()->size());
}