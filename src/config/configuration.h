/*
 * AgentSpeak code:
 *
 * // Agent Alice.
 * 
 * !start.
 * !is_day. //Ask Bob if it's day
 * its_day. 
 * its_night.
 * 
 * +!start <- say_start.
 * 
 * +!hello <- say_hello .broadcast(achieve,is_day).
 * 
 * +its_day <- say_its_day.
 * +its_night <- say_its_night.
 * 
 * 
 */ 

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "bdi/belief_base.h"
#include "bdi/event_base.h"
#include "bdi/plan_base.h"
#include "bdi/intention_base.h"
#include "communication/msg_list.h"
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
  MsgList list; // List of propositions used for communication.
  Communicator communicator; // Object used for communication.

public:
  AgentSettings()
  {
    belief_base = BeliefBase(2);
    event_base = EventBase(6);
    plan_base = PlanBase(4);
    intention_base = IntentionBase(10, 4);


    // Mapping propositions to enable communication between agents.
    list.addItem("its_night", 1, false);
    list.addItem("its_day", 0, false);
    list.addItem("say_start", 4, false);
    list.addItem(".broadcast", 7, false);
    list.addItem("start", 2, false);
    list.addItem("say_its_day", 8, false);
    list.addItem("is_day", 3, false);
    list.addItem("say_hello", 6, false);
    list.addItem("say_its_night", 9, false);
    list.addItem("hello", 5, false);
    communicator = Communicator(&list);

    //--------------------------------------------------------------------------

    Belief belief_its_day(0, nullptr, true);
    belief_base.add_belief(belief_its_day);

    //--------------------------------------------------------------------------

    Belief belief_its_night(1, nullptr, true);
    belief_base.add_belief(belief_its_night);

    //--------------------------------------------------------------------------

    Event event_2(EventOperator::GOAL_ADDITION, 2);
    event_base.add_event(event_2);

    //--------------------------------------------------------------------------

    Event event_3(EventOperator::GOAL_ADDITION, 3);
    event_base.add_event(event_3);

    //--------------------------------------------------------------------------

    Proposition prop_0(2);
    context_0 = Context(0);
    body_0 = Body(1);

    Proposition prop_0_body_0(4);
    BodyInstruction inst_0_0(BodyType::ACTION, prop_0_body_0, action_say_start);
    body_0.add_instruction(inst_0_0);

    Plan plan_0(EventOperator::GOAL_ADDITION, prop_0, &context_0, &body_0);
    plan_base.add_plan(plan_0);

    //--------------------------------------------------------------------------

    Proposition prop_1(5);
    context_1 = Context(0);
    body_1 = Body(2);

    Proposition prop_1_body_0(6);
    BodyInstruction inst_0_1(BodyType::ACTION, prop_1_body_0, action_say_hello);
    body_1.add_instruction(inst_0_1);

    Proposition prop_1_body_1(7);
    BodyInstruction inst_1_1(BodyType::INTERNAL_ACTION, prop_1_body_1, communicator.internal_action_broadcast);
    /* ToBeUncommented: */inst_1_1.add_arg(CENUMFOR_ILF::ACHIEVE);
    /* ToBeUncommented: */inst_1_1.add_arg(list.searchByName("is_day")->prop);
    body_1.add_instruction(inst_1_1);

    Plan plan_1(EventOperator::GOAL_ADDITION, prop_1, &context_1, &body_1);
    plan_base.add_plan(plan_1);

    //--------------------------------------------------------------------------

    Proposition prop_2(0);
    context_2 = Context(0);
    body_2 = Body(1);

    Proposition prop_2_body_0(8);
    BodyInstruction inst_0_2(BodyType::ACTION, prop_2_body_0, action_say_its_day);
    body_2.add_instruction(inst_0_2);

    Plan plan_2(EventOperator::BELIEF_ADDITION, prop_2, &context_2, &body_2);
    plan_base.add_plan(plan_2);

    //--------------------------------------------------------------------------

    Proposition prop_3(1);
    context_3 = Context(0);
    body_3 = Body(1);

    Proposition prop_3_body_0(9);
    BodyInstruction inst_0_3(BodyType::ACTION, prop_3_body_0, action_say_its_night);
    body_3.add_instruction(inst_0_3);

    Plan plan_3(EventOperator::BELIEF_ADDITION, prop_3, &context_3, &body_3);
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