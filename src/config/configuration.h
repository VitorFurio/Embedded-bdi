/*
 * AgentSpeak code:
 *
 * // file used to test translator
 * +sad.
 * !start.
 * 
 * +!start <- +happy.
 * 
 * +happy <- !!hello; .broadcast(achieve,happy).
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
#include "communication/communicator.h"
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
  Body body_3;
  Context context_3;
  BeliefBase belief_base;
  EventBase event_base;
  PlanBase plan_base;
  IntentionBase intention_base;
  HashTable table; // Map of propositions used for communication.
  Communicator communicator; // Object used for communication.

public:
  AgentSettings()
  {
    belief_base = BeliefBase(2);
    event_base = EventBase(6);
    plan_base = PlanBase(4);
    intention_base = IntentionBase(10, 4);


    // Mapping propositions to enable communication between agents.
    table.addItem("happy", 0, true);
    table.addItem("sad", 1, true);
    table.addItem(".broadcast", 4, true);
    table.addItem("start", 2, true);
    table.addItem("say_hello", 5, true);
    table.addItem("hello", 3, true);
    communicator = Communicator(&table);

    //--------------------------------------------------------------------------

    Belief belief_happy(0, nullptr, false);
    belief_base.add_belief(belief_happy);

    //--------------------------------------------------------------------------

    Belief belief_sad(1, nullptr, false);
    belief_base.add_belief(belief_sad);

    //--------------------------------------------------------------------------

    Event event_2(EventOperator::GOAL_ADDITION, 2);
    event_base.add_event(event_2);

    //--------------------------------------------------------------------------

    Proposition prop_0(1);
    context_0 = Context(0);
    body_0 = Body(0);

    Plan plan_0(EventOperator::BELIEF_ADDITION, prop_0, &context_0, &body_0);
    plan_base.add_plan(plan_0);

    //--------------------------------------------------------------------------

    Proposition prop_1(2);
    context_1 = Context(0);
    body_1 = Body(1);

    Proposition prop_1_body_0(0);
    BodyInstruction inst_0_1(BodyType::BELIEF, prop_1_body_0, EventOperator::BELIEF_ADDITION);
    body_1.add_instruction(inst_0_1);

    Plan plan_1(EventOperator::GOAL_ADDITION, prop_1, &context_1, &body_1);
    plan_base.add_plan(plan_1);

    //--------------------------------------------------------------------------

    Proposition prop_2(0);
    context_2 = Context(0);
    body_2 = Body(2);

    Proposition prop_2_body_0(3);
    BodyInstruction inst_0_2(BodyType::GOAL, prop_2_body_0, EventOperator::GOAL_ACHIEVE);
    body_2.add_instruction(inst_0_2);

    Proposition prop_2_body_1(4);
    BodyInstruction inst_1_2(BodyType::INTERNAL_ACTION, prop_2_body_1, communicator.internal_action_broadcast,belief_happy.get_proposition());
    /* ToBeUncommented: */inst_1_2.add_arg(CENUMFOR_ILF::ACHIEVE);
    ///* ToBeUncommented: */inst_1_2.add_arg(&belief_happy);
    /* ToBeUncommented: */inst_1_2.add_arg(belief_happy.get_proposition());
    body_2.add_instruction(inst_1_2);

    Plan plan_2(EventOperator::BELIEF_ADDITION, prop_2, &context_2, &body_2);
    plan_base.add_plan(plan_2);

    //--------------------------------------------------------------------------

    Proposition prop_3(3);
    context_3 = Context(0);
    body_3 = Body(1);

    Proposition prop_3_body_0(5);
    BodyInstruction inst_0_3(BodyType::ACTION, prop_3_body_0, action_say_hello);
    body_3.add_instruction(inst_0_3);

    Plan plan_3(EventOperator::GOAL_ADDITION, prop_3, &context_3, &body_3);
    plan_base.add_plan(plan_3);
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
  Communicator * get_communicator()
  {
    return &communicator;
  }
};

#endif /*CONFIGURATION_H_ */