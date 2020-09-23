/*
 * configuration.h
 *
 *  Created on: Sep 15, 2020
 *      Author: Matuzalem Muller
 */

#ifndef UTEST_AGENT_MULTIPLE_INTENTIONS_CONFIGURATION_H_
#define UTEST_AGENT_MULTIPLE_INTENTIONS_CONFIGURATION_H_

#include "../../lib/bdi/belief_base.h"
#include "../../lib/bdi/event_base.h"
#include "../../lib/bdi/plan_base.h"
#include "../../lib/bdi/intention_base.h"
#include "functions.h"

class MultipleIntentions
{
private:
  BeliefBase * belief_base;
  EventBase * event_base;
  PlanBase * plan_base;
  IntentionBase * intention_base;

public:
  MultipleIntentions()
  {
    belief_base = new BeliefBase(0);
    event_base = new EventBase(3);
    plan_base = new PlanBase(6);
    intention_base = new IntentionBase(3, 4);

    //--------------------------------------------------------------------------

    Event event_1(EventOperator::GOAL_ADDITION, 0);
    event_base->add_event(event_1);

    //--------------------------------------------------------------------------

    Event event_2(EventOperator::GOAL_ADDITION, 1);
    event_base->add_event(event_2);

    //--------------------------------------------------------------------------

    Event event_3(EventOperator::GOAL_ADDITION, 2);
    event_base->add_event(event_3);

    //--------------------------------------------------------------------------

    Statement stm_0(0);
    Context * context_0 = new Context(0);
    Body * body_0 = new Body(2);

    Statement stm_0_body_0(3);
    BodyInstruction inst_0_0(BodyType::ACTION, stm_0_body_0, action_1_multiple_intentions);
    body_0->add_instruction(inst_0_0);

    Statement stm_0_body_1(4);
    BodyInstruction inst_1_0(BodyType::GOAL, stm_0_body_1, EventOperator::GOAL_ADDITION);
    body_0->add_instruction(inst_1_0);

    Plan plan_0(EventOperator::GOAL_ADDITION, stm_0, context_0, body_0);
    plan_base->add_plan(plan_0);

    //--------------------------------------------------------------------------

    Statement stm_1(4);
    Context * context_1 = new Context(0);
    Body * body_1 = new Body(1);

    Statement stm_1_body_0(5);
    BodyInstruction inst_0_1(BodyType::ACTION, stm_1_body_0, action_2_multiple_intentions);
    body_1->add_instruction(inst_0_1);

    Plan plan_1(EventOperator::GOAL_ADDITION, stm_1, context_1, body_1);
    plan_base->add_plan(plan_1);

    //--------------------------------------------------------------------------

    Statement stm_2(1);
    Context * context_2 = new Context(0);
    Body * body_2 = new Body(2);

    Statement stm_2_body_0(6);
    BodyInstruction inst_0_2(BodyType::ACTION, stm_2_body_0, action_3_multiple_intentions);
    body_2->add_instruction(inst_0_2);

    Statement stm_2_body_1(7);
    BodyInstruction inst_1_2(BodyType::GOAL, stm_2_body_1, EventOperator::GOAL_ADDITION);
    body_2->add_instruction(inst_1_2);

    Plan plan_2(EventOperator::GOAL_ADDITION, stm_2, context_2, body_2);
    plan_base->add_plan(plan_2);

    //--------------------------------------------------------------------------

    Statement stm_3(7);
    Context * context_3 = new Context(0);
    Body * body_3 = new Body(1);

    Statement stm_3_body_0(8);
    BodyInstruction inst_0_3(BodyType::ACTION, stm_3_body_0, action_4_multiple_intentions);
    body_3->add_instruction(inst_0_3);

    Plan plan_3(EventOperator::GOAL_ADDITION, stm_3, context_3, body_3);
    plan_base->add_plan(plan_3);

    //--------------------------------------------------------------------------

    Statement stm_4(2);
    Context * context_4 = new Context(0);
    Body * body_4 = new Body(2);

    Statement stm_4_body_0(9);
    BodyInstruction inst_0_4(BodyType::ACTION, stm_4_body_0, action_5_multiple_intentions);
    body_4->add_instruction(inst_0_4);

    Statement stm_4_body_1(10);
    BodyInstruction inst_1_4(BodyType::GOAL, stm_4_body_1, EventOperator::GOAL_ADDITION);
    body_4->add_instruction(inst_1_4);

    Plan plan_4(EventOperator::GOAL_ADDITION, stm_4, context_4, body_4);
    plan_base->add_plan(plan_4);

    //--------------------------------------------------------------------------

    Statement stm_5(10);
    Context * context_5 = new Context(0);
    Body * body_5 = new Body(1);

    Statement stm_5_body_0(11);
    BodyInstruction inst_0_5(BodyType::ACTION, stm_5_body_0, action_6_multiple_intentions);
    body_5->add_instruction(inst_0_5);

    Plan plan_5(EventOperator::GOAL_ADDITION, stm_5, context_5, body_5);
    plan_base->add_plan(plan_5);
  }

  ~MultipleIntentions()
  {
    delete belief_base;
    delete event_base;
    delete plan_base;
    delete intention_base;
  }

  BeliefBase *  get_belief_base()
  {
    return belief_base;
  }

  EventBase * get_event_base()
  {
    return event_base;
  }

  PlanBase * get_plan_base()
  {
    return plan_base;
  }

  IntentionBase * get_intention_base()
  {
    return intention_base;
  }
};

#endif /* UTEST_AGENT_MULTIPLE_INTENTIONS_CONFIGURATION_H_ */
