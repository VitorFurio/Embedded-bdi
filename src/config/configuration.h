/*
 * AgentSpeak code:
 *
 * // Agent Alice.
 * 
 * !start.
 * !is_day. //agents only send beliefs and goals that they themselves have. 
 * 
 * +!start <- .broadcast(achieve,hello).
 * 
 * +!hello <- say_hello .broadcast(achieve,is_day).
 * 
 * //+happy <- .broadcast(achieve,hello).
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
  BeliefBase belief_base;
  EventBase event_base;
  PlanBase plan_base;
  IntentionBase intention_base;
  MsgList list; // List of propositions used for communication.
  Communicator communicator; // Object used for communication.

public:
  AgentSettings()
  {
    belief_base = BeliefBase(0);
    event_base = EventBase(6);
    plan_base = PlanBase(2);
    intention_base = IntentionBase(10, 4);


    // Mapping propositions to enable communication between agents.
    list.addItem(".broadcast", 2, false);
    list.addItem("start", 0, false);
    list.addItem("is_day", 1, false);
    list.addItem("say_hello", 4, false);
    list.addItem("hello", 3, false);
    communicator = Communicator(&list);

    //--------------------------------------------------------------------------

    Event event_0(EventOperator::GOAL_ADDITION, 0);
    event_base.add_event(event_0);

    //--------------------------------------------------------------------------

    Event event_1(EventOperator::GOAL_ADDITION, 1);
    event_base.add_event(event_1);

    //--------------------------------------------------------------------------

    Proposition prop_0(0);
    context_0 = Context(0);
    body_0 = Body(1);

    Proposition prop_0_body_0(2);
    BodyInstruction inst_0_0(BodyType::INTERNAL_ACTION, prop_0_body_0, communicator.internal_action_broadcast);
    /* ToBeUncommented: */inst_0_0.add_arg(CENUMFOR_ILF::ACHIEVE);
    /* ToBeUncommented: */inst_0_0.add_arg(list.searchByName("hello")->prop);
    body_0.add_instruction(inst_0_0);

    Plan plan_0(EventOperator::GOAL_ADDITION, prop_0, &context_0, &body_0);
    plan_base.add_plan(plan_0);

    //--------------------------------------------------------------------------

    Proposition prop_1(3);
    context_1 = Context(0);
    body_1 = Body(2);

    Proposition prop_1_body_0(4);
    BodyInstruction inst_0_1(BodyType::ACTION, prop_1_body_0, action_say_hello);
    body_1.add_instruction(inst_0_1);

    Proposition prop_1_body_1(2);
    BodyInstruction inst_1_1(BodyType::INTERNAL_ACTION, prop_1_body_1, communicator.internal_action_broadcast);
    /* ToBeUncommented: */inst_1_1.add_arg(CENUMFOR_ILF::ACHIEVE);
    /* ToBeUncommented: */inst_1_1.add_arg(list.searchByName("is_day")->prop);
    body_1.add_instruction(inst_1_1);

    Plan plan_1(EventOperator::GOAL_ADDITION, prop_1, &context_1, &body_1);
    plan_base.add_plan(plan_1);
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