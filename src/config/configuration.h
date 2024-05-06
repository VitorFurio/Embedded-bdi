/*
 * AgentSpeak code:
 *
 * // file used to test translator
 * 
 * !start.
 * 
 * +!start <- +happy.
 * 
 * +happy <- !!hello; .broadcast(tell,happy).
 * 
 * +!hello <- say_hello.
 */ 

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "bdi/belief_base.h"
#include "bdi/event_base.h"
#include "bdi/plan_base.h"
#include "bdi/intention_base.h"
#include "communication/hash_table.h"
#include "../../data/functions.h"

class AgentSettings
{
private:
  Body body_0;
  Context context_0;
  Body body_1;
  Context context_1;
  Body body_2;
  Context context_2;
  BeliefBase belief_base;
  EventBase event_base;
  PlanBase plan_base;
  IntentionBase intention_base;
  HashTable table; //Map of propositions used for communication.

public:
  AgentSettings()
  {
    belief_base = BeliefBase(1);
    event_base = EventBase(6);
    plan_base = PlanBase(3);
    intention_base = IntentionBase(10, 4);

    //--------------------------------------------------------------------------

    Belief belief_happy(0, nullptr, false);
    belief_base.add_belief(belief_happy);

    //--------------------------------------------------------------------------

    Event event_1(EventOperator::GOAL_ADDITION, 1);
    event_base.add_event(event_1);

    //--------------------------------------------------------------------------

    Proposition prop_0(1);
    context_0 = Context(0);
    body_0 = Body(1);

    Proposition prop_0_body_0(0);
    BodyInstruction inst_0_0(BodyType::BELIEF, prop_0_body_0, EventOperator::BELIEF_ADDITION);
    body_0.add_instruction(inst_0_0);

    Plan plan_0(EventOperator::GOAL_ADDITION, prop_0, &context_0, &body_0);
    plan_base.add_plan(plan_0);

    //--------------------------------------------------------------------------

    Proposition prop_1(0);
    context_1 = Context(0);
    body_1 = Body(2);

    Proposition prop_1_body_0(2);
    BodyInstruction inst_0_1(BodyType::GOAL, prop_1_body_0, EventOperator::GOAL_ACHIEVE);
    body_1.add_instruction(inst_0_1);

    Proposition prop_1_body_1(3);
    BodyInstruction inst_1_1(BodyType::INTERNAL_ACTION, prop_1_body_1, internal_action_broadcast);
    /* ToBeUncommented: */inst_1_1.add_arg(CENUMFOR_ILF::TELL);
    //* ToBeUncommented: /inst_1_1.add_arg(belief_happy);
    body_1.add_instruction(inst_1_1);

    Plan plan_1(EventOperator::BELIEF_ADDITION, prop_1, &context_1, &body_1);
    plan_base.add_plan(plan_1);

    //--------------------------------------------------------------------------

    Proposition prop_2(2);
    context_2 = Context(0);
    body_2 = Body(1);

    Proposition prop_2_body_0(4);
    BodyInstruction inst_0_2(BodyType::ACTION, prop_2_body_0, action_say_hello);
    body_2.add_instruction(inst_0_2);

    Plan plan_2(EventOperator::GOAL_ADDITION, prop_2, &context_2, &body_2);
    plan_base.add_plan(plan_2);
  //Mapping propositions to enable communication between agents.
  table.addItem("happy", 0, true);
  table.addItem(".broadcast", 3, true);
  table.addItem("start", 1, true);
  table.addItem("say_hello", 4, true);
  table.addItem("hello", 2, true);

  }

  BeliefBase * get_belief_base()
  {
    return &belief_base;
  }

  EventBase * get_event_base()
  {
    return &event_base;
  }

  PlanBase * get_plan_base()
  {
    return &plan_base;
  }

  IntentionBase * get_intention_base()
  {
    return &intention_base;
  }
};

#endif /*CONFIGURATION_H_ */