/*
 * agent_loop.cpp
 *
 *  Created on: Jun 28, 2020
 *      Author: Matuzalem Muller
 */

#include <iostream>
#include "../lib/bdi/belief_base.h"
#include "../lib/bdi/event_base.h"
#include "../lib/bdi/plan_base.h"
#include "../lib/bdi/intention_base.h"

using namespace std;

bool compile_test = true;

int main()
{
  int bb_size = 4;
  int eb_size = 4;
  int pb_size = 4;
  int ib_queue_size = 4;
  int ib_stack_size = 2;

  BeliefBase beliefs(bb_size);
  EventBase events(eb_size);
  PlanBase plans(pb_size);
  IntentionBase intentions(ib_queue_size, ib_stack_size);

  Event * event_to_process;
  Plan * plan_to_act;

  while(true)
  {
    // Update beliefs
    beliefs.update(&events);

    // Checks if there are events to be processed
    if (!events.is_empty())
    {
      event_to_process = events.get_event();
      if(event_to_process)
      {
        plan_to_act = plans.revise(event_to_process, &beliefs);
        if (plan_to_act) {
          intentions.add_intention(plan_to_act);
        }
      }
    }

    // Runs intention in case there are any
    if (!intentions.is_empty())
    {
      intentions.run_intention_base(&beliefs, &events);
    }

    if (compile_test == true)
    {
      std::cout << "Compilation successful!" << std::endl;
      break;
    }
  }

  return 0;
}
