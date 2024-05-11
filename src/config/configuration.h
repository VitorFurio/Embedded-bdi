/*
 * AgentSpeak code:
 *
 * // file used to test translator
 * //+teste.
 * 
 * +test : test2 <- say_test.
 * 
 * -test2 <- .broadcast(achieve,happy).
 * !start.
 * 
 * +!start <- +happy.
 * 
 * +happy <- !!hello; .broadcast(achieve,happy).
 * 
 * +!hello <- say_hello.
 * -!hello <- say_test.
 */ 

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "bdi/belief_base.h"
#include "bdi/event_base.h"
#include "bdi/plan_base.h"
#include "bdi/intention_base.h"
#include "communication/hash_table.h"
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
  Body body_4;
  Context context_4;
  Body body_5;
  Context context_5;
  BeliefBase belief_base;
  EventBase event_base;
  PlanBase plan_base;
  IntentionBase intention_base;
 // HashTable table; // Map of propositions used for communication.
  MsgList table; // Map of propositions used for communication.
  Communicator communicator; // Object used for communication.

public:
  AgentSettings()
  {
    belief_base = BeliefBase(3);
    event_base = EventBase(6);
    plan_base = PlanBase(6);
    intention_base = IntentionBase(10, 4);


    // Mapping propositions to enable communication between agents.
    table.addItem("test2", 2, false);
    table.addItem("test", 1, false);
    table.addItem("happy", 0, false);
    table.addItem(".broadcast", 5, false);
    table.addItem("start", 3, false);
    table.addItem("say_test", 4, false);
    table.addItem("say_hello", 7, false);
    table.addItem("hello", 6, false);
    communicator = Communicator(&table);

    //--------------------------------------------------------------------------

    Belief belief_happy(0, nullptr, false);
    belief_base.add_belief(belief_happy);

    //--------------------------------------------------------------------------

    Belief belief_test(1, nullptr, false);
    belief_base.add_belief(belief_test);

    //--------------------------------------------------------------------------

    Belief belief_test2(2, nullptr, false);
    belief_base.add_belief(belief_test2);

    //--------------------------------------------------------------------------

    Event event_3(EventOperator::GOAL_ADDITION, 3);
    event_base.add_event(event_3);

    //--------------------------------------------------------------------------

    Proposition prop_0(1);
    context_0 = Context(1);
    body_0 = Body(1);

    Proposition prop_0_test2(2);
    ContextCondition cond_0_0(prop_0_test2);
    context_0.add_context(cond_0_0);

    Proposition prop_0_body_0(4);
    BodyInstruction inst_0_0(BodyType::ACTION, prop_0_body_0, action_say_test);
    body_0.add_instruction(inst_0_0);

    Plan plan_0(EventOperator::BELIEF_ADDITION, prop_0, &context_0, &body_0);
    plan_base.add_plan(plan_0);

    //--------------------------------------------------------------------------

    Proposition prop_1(2);
    context_1 = Context(0);
    body_1 = Body(1);

    Proposition prop_1_body_0(5);
    BodyInstruction inst_0_1(BodyType::INTERNAL_ACTION, prop_1_body_0, communicator.internal_action_broadcast,belief_happy.get_proposition());
    /* ToBeUncommented: */inst_0_1.add_arg(CENUMFOR_ILF::ACHIEVE);
    ///* ToBeUncommented: */inst_0_1.add_arg(&belief_happy);
    /* ToBeUncommented: */inst_0_1.add_arg(belief_happy.get_proposition());
    body_1.add_instruction(inst_0_1);

    Plan plan_1(EventOperator::BELIEF_DELETION, prop_1, &context_1, &body_1);
    plan_base.add_plan(plan_1);

    //--------------------------------------------------------------------------

    Proposition prop_2(3);
    context_2 = Context(0);
    body_2 = Body(1);

    Proposition prop_2_body_0(0);
    BodyInstruction inst_0_2(BodyType::BELIEF, prop_2_body_0, EventOperator::BELIEF_ADDITION);
    body_2.add_instruction(inst_0_2);

    Plan plan_2(EventOperator::GOAL_ADDITION, prop_2, &context_2, &body_2);
    plan_base.add_plan(plan_2);

    //--------------------------------------------------------------------------

    Proposition prop_3(0);
    context_3 = Context(0);
    body_3 = Body(2);

    Proposition prop_3_body_0(6);
    BodyInstruction inst_0_3(BodyType::GOAL, prop_3_body_0, EventOperator::GOAL_ACHIEVE);
    body_3.add_instruction(inst_0_3);

    Proposition prop_3_body_1(5);
    BodyInstruction inst_1_3(BodyType::INTERNAL_ACTION, prop_3_body_1, communicator.internal_action_broadcast,belief_happy.get_proposition());
    /* ToBeUncommented: */inst_1_3.add_arg(CENUMFOR_ILF::ACHIEVE);
    ///* ToBeUncommented: */inst_1_3.add_arg(&belief_happy);
    /* ToBeUncommented: */inst_1_3.add_arg(belief_happy.get_proposition());
    body_3.add_instruction(inst_1_3);

    Plan plan_3(EventOperator::BELIEF_ADDITION, prop_3, &context_3, &body_3);
    plan_base.add_plan(plan_3);

    //--------------------------------------------------------------------------

    Proposition prop_4(6);
    context_4 = Context(0);
    body_4 = Body(1);

    Proposition prop_4_body_0(7);
    BodyInstruction inst_0_4(BodyType::ACTION, prop_4_body_0, action_say_hello);
    body_4.add_instruction(inst_0_4);

    Plan plan_4(EventOperator::GOAL_ADDITION, prop_4, &context_4, &body_4);
    plan_base.add_plan(plan_4);

    //--------------------------------------------------------------------------

    Proposition prop_5(6);
    context_5 = Context(0);
    body_5 = Body(1);

    Proposition prop_5_body_0(4);
    BodyInstruction inst_0_5(BodyType::ACTION, prop_5_body_0, action_say_test);
    body_5.add_instruction(inst_0_5);

    Plan plan_5(EventOperator::GOAL_DELETION, prop_5, &context_5, &body_5);
    plan_base.add_plan(plan_5);
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