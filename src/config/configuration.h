/*
 * AgentSpeak code:
 *
 * // Monitoramento e Alerta em uma Rede de Sensores
 * !start.
 * 
 * // Condições iniciais
 * +!start : true <-
 *     .my_name("sensor1");
 *     -sensor1;
 *     -sensor2;
 *     -sensor3;
 *     print_init.
 * 
 * // Reação ao ambiente e sociabilidade
 * +fire : true <- print_fire; +sensor1; +alert; .broadcast(tell,sensor1).
 * -fire : true <- print_not_fire; -sensor1; .broadcast(untell,sensor1).
 * 
 * // Reação a mensagens
 * +sensor2 <- +alert.
 * +sensor3 <- +alert.
 * +alert <- print_alert; !!check_alarm_condition.
 * 
 * // Se pelo menos 2 sensores dispararem, o alarme é acionado.
 * +!check_alarm_condition: sensor1 & sensor2 <- trigger_alarm.
 * +!check_alarm_condition: sensor2 & sensor3 <- trigger_alarm.
 * +!check_alarm_condition: sensor3 & sensor1 <- trigger_alarm.
 * 
 * +!check_alarm_condition: sensor1 <- !!check_alarm_condition.
 * +!check_alarm_condition: sensor2 <- !!check_alarm_condition.
 * +!check_alarm_condition: sensor3 <- !!check_alarm_condition.
 * 
 * +!check_alarm_condition: true <- print_default; -alert. //!check_alarm_condition.
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
  Body body_4;
  Context context_4;
  Body body_5;
  Context context_5;
  Body body_6;
  Context context_6;
  Body body_7;
  Context context_7;
  Body body_8;
  Context context_8;
  Body body_9;
  Context context_9;
  Body body_10;
  Context context_10;
  Body body_11;
  Context context_11;
  Body body_12;
  Context context_12;
  BeliefBase belief_base;
  EventBase event_base;
  PlanBase plan_base;
  IntentionBase intention_base;
  MsgList list; // List of propositions used for communication.
  Communicator communicator; // Object used for communication.

public:
  AgentSettings()
  {
    belief_base = BeliefBase(5);
    event_base = EventBase(10);
    plan_base = PlanBase(13);
    intention_base = IntentionBase(15, 10);


    // Mapping propositions to enable communication between agents.
    list.addItem("print_init", 7, false);
    list.addItem("print_alert", 11, false);
    list.addItem(".broadcast", 9, false);
    list.addItem("start", 5, false);
    list.addItem("print_fire", 8, false);
    list.addItem("trigger_alarm", 13, false);
    list.addItem("sensor2", 3, false);
    list.addItem("sensor3", 4, false);
    list.addItem("alert", 0, false);
    list.addItem(".my_name", 6, false);
    list.addItem("print_not_fire", 10, false);
    list.addItem("fire", 1, false);
    list.addItem("check_alarm_condition", 12, false);
    list.addItem("sensor1", 2, false);
    list.addItem("print_default", 14, false);
    list.print();
    communicator = Communicator(&list);

    //--------------------------------------------------------------------------

    Belief belief_alert(0, nullptr, false);
    belief_base.add_belief(belief_alert);

    //--------------------------------------------------------------------------

    Belief belief_fire(1, update_fire, false);
    belief_base.add_belief(belief_fire);

    //--------------------------------------------------------------------------

    Belief belief_sensor1(2, nullptr, false);
    belief_base.add_belief(belief_sensor1);

    //--------------------------------------------------------------------------

    Belief belief_sensor2(3, nullptr, false);
    belief_base.add_belief(belief_sensor2);

    //--------------------------------------------------------------------------

    Belief belief_sensor3(4, nullptr, false);
    belief_base.add_belief(belief_sensor3);

    //--------------------------------------------------------------------------

    Event event_5(EventOperator::GOAL_ADDITION, 5);
    event_base.add_event(event_5);

    //--------------------------------------------------------------------------

    Proposition prop_0(5);
    context_0 = Context(0);
    body_0 = Body(5);

    Proposition prop_0_body_0(6);
    BodyInstruction inst_0_0(BodyType::INTERNAL_ACTION, prop_0_body_0, communicator.internal_action_my_name);
    communicator.setName("sensor1");
    body_0.add_instruction(inst_0_0);

    Proposition prop_0_body_1(2);
    BodyInstruction inst_1_0(BodyType::BELIEF, prop_0_body_1, EventOperator::BELIEF_DELETION);
    body_0.add_instruction(inst_1_0);

    Proposition prop_0_body_2(3);
    BodyInstruction inst_2_0(BodyType::BELIEF, prop_0_body_2, EventOperator::BELIEF_DELETION);
    body_0.add_instruction(inst_2_0);

    Proposition prop_0_body_3(4);
    BodyInstruction inst_3_0(BodyType::BELIEF, prop_0_body_3, EventOperator::BELIEF_DELETION);
    body_0.add_instruction(inst_3_0);

    Proposition prop_0_body_4(7);
    BodyInstruction inst_4_0(BodyType::ACTION, prop_0_body_4, action_print_init);
    body_0.add_instruction(inst_4_0);

    Plan plan_0(EventOperator::GOAL_ADDITION, prop_0, &context_0, &body_0);
    plan_base.add_plan(plan_0);

    //--------------------------------------------------------------------------

    Proposition prop_1(1);
    context_1 = Context(0);
    body_1 = Body(4);

    Proposition prop_1_body_0(8);
    BodyInstruction inst_0_1(BodyType::ACTION, prop_1_body_0, action_print_fire);
    body_1.add_instruction(inst_0_1);

    Proposition prop_1_body_1(2);
    BodyInstruction inst_1_1(BodyType::BELIEF, prop_1_body_1, EventOperator::BELIEF_ADDITION);
    body_1.add_instruction(inst_1_1);

    Proposition prop_1_body_2(0);
    BodyInstruction inst_2_1(BodyType::BELIEF, prop_1_body_2, EventOperator::BELIEF_ADDITION);
    body_1.add_instruction(inst_2_1);

    Proposition prop_1_body_3(9);
    BodyInstruction inst_3_1(BodyType::INTERNAL_ACTION, prop_1_body_3, communicator.internal_action_broadcast);
    inst_3_1.add_arg(CENUMFOR_ILF::TELL);
    inst_3_1.add_arg(list.searchByName("sensor1")->prop);
    body_1.add_instruction(inst_3_1);

    Plan plan_1(EventOperator::BELIEF_ADDITION, prop_1, &context_1, &body_1);
    plan_base.add_plan(plan_1);

    //--------------------------------------------------------------------------

    Proposition prop_2(1);
    context_2 = Context(0);
    body_2 = Body(3);

    Proposition prop_2_body_0(10);
    BodyInstruction inst_0_2(BodyType::ACTION, prop_2_body_0, action_print_not_fire);
    body_2.add_instruction(inst_0_2);

    Proposition prop_2_body_1(2);
    BodyInstruction inst_1_2(BodyType::BELIEF, prop_2_body_1, EventOperator::BELIEF_DELETION);
    body_2.add_instruction(inst_1_2);

    Proposition prop_2_body_2(9);
    BodyInstruction inst_2_2(BodyType::INTERNAL_ACTION, prop_2_body_2, communicator.internal_action_broadcast);
    inst_2_2.add_arg(CENUMFOR_ILF::UNTELL);
    inst_2_2.add_arg(list.searchByName("sensor1")->prop);
    body_2.add_instruction(inst_2_2);

    Plan plan_2(EventOperator::BELIEF_DELETION, prop_2, &context_2, &body_2);
    plan_base.add_plan(plan_2);

    //--------------------------------------------------------------------------

    Proposition prop_3(3);
    context_3 = Context(0);
    body_3 = Body(1);

    Proposition prop_3_body_0(0);
    BodyInstruction inst_0_3(BodyType::BELIEF, prop_3_body_0, EventOperator::BELIEF_ADDITION);
    body_3.add_instruction(inst_0_3);

    Plan plan_3(EventOperator::BELIEF_ADDITION, prop_3, &context_3, &body_3);
    plan_base.add_plan(plan_3);

    //--------------------------------------------------------------------------

    Proposition prop_4(4);
    context_4 = Context(0);
    body_4 = Body(1);

    Proposition prop_4_body_0(0);
    BodyInstruction inst_0_4(BodyType::BELIEF, prop_4_body_0, EventOperator::BELIEF_ADDITION);
    body_4.add_instruction(inst_0_4);

    Plan plan_4(EventOperator::BELIEF_ADDITION, prop_4, &context_4, &body_4);
    plan_base.add_plan(plan_4);

    //--------------------------------------------------------------------------

    Proposition prop_5(0);
    context_5 = Context(0);
    body_5 = Body(2);

    Proposition prop_5_body_0(11);
    BodyInstruction inst_0_5(BodyType::ACTION, prop_5_body_0, action_print_alert);
    body_5.add_instruction(inst_0_5);

    Proposition prop_5_body_1(12);
    BodyInstruction inst_1_5(BodyType::GOAL, prop_5_body_1, EventOperator::GOAL_ACHIEVE);
    body_5.add_instruction(inst_1_5);

    Plan plan_5(EventOperator::BELIEF_ADDITION, prop_5, &context_5, &body_5);
    plan_base.add_plan(plan_5);

    //--------------------------------------------------------------------------

    Proposition prop_6(12);
    context_6 = Context(2);
    body_6 = Body(1);

    Proposition prop_6_sensor1(2);
    ContextCondition cond_6_0(prop_6_sensor1);
    context_6.add_context(cond_6_0);

    Proposition prop_6_sensor2(3);
    ContextCondition cond_6_1(prop_6_sensor2);
    context_6.add_context(cond_6_1);

    Proposition prop_6_body_0(13);
    BodyInstruction inst_0_6(BodyType::ACTION, prop_6_body_0, action_trigger_alarm);
    body_6.add_instruction(inst_0_6);

    Plan plan_6(EventOperator::GOAL_ADDITION, prop_6, &context_6, &body_6);
    plan_base.add_plan(plan_6);

    //--------------------------------------------------------------------------

    Proposition prop_7(12);
    context_7 = Context(2);
    body_7 = Body(1);

    Proposition prop_7_sensor2(3);
    ContextCondition cond_7_0(prop_7_sensor2);
    context_7.add_context(cond_7_0);

    Proposition prop_7_sensor3(4);
    ContextCondition cond_7_1(prop_7_sensor3);
    context_7.add_context(cond_7_1);

    Proposition prop_7_body_0(13);
    BodyInstruction inst_0_7(BodyType::ACTION, prop_7_body_0, action_trigger_alarm);
    body_7.add_instruction(inst_0_7);

    Plan plan_7(EventOperator::GOAL_ADDITION, prop_7, &context_7, &body_7);
    plan_base.add_plan(plan_7);

    //--------------------------------------------------------------------------

    Proposition prop_8(12);
    context_8 = Context(2);
    body_8 = Body(1);

    Proposition prop_8_sensor3(4);
    ContextCondition cond_8_0(prop_8_sensor3);
    context_8.add_context(cond_8_0);

    Proposition prop_8_sensor1(2);
    ContextCondition cond_8_1(prop_8_sensor1);
    context_8.add_context(cond_8_1);

    Proposition prop_8_body_0(13);
    BodyInstruction inst_0_8(BodyType::ACTION, prop_8_body_0, action_trigger_alarm);
    body_8.add_instruction(inst_0_8);

    Plan plan_8(EventOperator::GOAL_ADDITION, prop_8, &context_8, &body_8);
    plan_base.add_plan(plan_8);

    //--------------------------------------------------------------------------

    Proposition prop_9(12);
    context_9 = Context(1);
    body_9 = Body(1);

    Proposition prop_9_sensor1(2);
    ContextCondition cond_9_0(prop_9_sensor1);
    context_9.add_context(cond_9_0);

    Proposition prop_9_body_0(12);
    BodyInstruction inst_0_9(BodyType::GOAL, prop_9_body_0, EventOperator::GOAL_ACHIEVE);
    body_9.add_instruction(inst_0_9);

    Plan plan_9(EventOperator::GOAL_ADDITION, prop_9, &context_9, &body_9);
    plan_base.add_plan(plan_9);

    //--------------------------------------------------------------------------

    Proposition prop_10(12);
    context_10 = Context(1);
    body_10 = Body(1);

    Proposition prop_10_sensor2(3);
    ContextCondition cond_10_0(prop_10_sensor2);
    context_10.add_context(cond_10_0);

    Proposition prop_10_body_0(12);
    BodyInstruction inst_0_10(BodyType::GOAL, prop_10_body_0, EventOperator::GOAL_ACHIEVE);
    body_10.add_instruction(inst_0_10);

    Plan plan_10(EventOperator::GOAL_ADDITION, prop_10, &context_10, &body_10);
    plan_base.add_plan(plan_10);

    //--------------------------------------------------------------------------

    Proposition prop_11(12);
    context_11 = Context(1);
    body_11 = Body(1);

    Proposition prop_11_sensor3(4);
    ContextCondition cond_11_0(prop_11_sensor3);
    context_11.add_context(cond_11_0);

    Proposition prop_11_body_0(12);
    BodyInstruction inst_0_11(BodyType::GOAL, prop_11_body_0, EventOperator::GOAL_ACHIEVE);
    body_11.add_instruction(inst_0_11);

    Plan plan_11(EventOperator::GOAL_ADDITION, prop_11, &context_11, &body_11);
    plan_base.add_plan(plan_11);

    //--------------------------------------------------------------------------

    Proposition prop_12(12);
    context_12 = Context(0);
    body_12 = Body(2);

    Proposition prop_12_body_0(14);
    BodyInstruction inst_0_12(BodyType::ACTION, prop_12_body_0, action_print_default);
    body_12.add_instruction(inst_0_12);

    Proposition prop_12_body_1(0);
    BodyInstruction inst_1_12(BodyType::BELIEF, prop_12_body_1, EventOperator::BELIEF_DELETION);
    body_12.add_instruction(inst_1_12);

    Plan plan_12(EventOperator::GOAL_ADDITION, prop_12, &context_12, &body_12);
    plan_base.add_plan(plan_12);
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