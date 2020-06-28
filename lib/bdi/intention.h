/*
 * intention.h
 *
 *  Created on: May 25, 2020
 *      Author: Matuzalem Muller
 */

#ifndef BDI_INTENTION_H_
#define BDI_INTENTION_H_

#include "belief_base.h"
#include "event_base.h"
#include "../lib/stack.h"
#include "../syntax/plan.h"

class Intention {
private:
  Stack<Body> _plans;
  int _size;

public:
  Intention();

  Intention(Plan plan, int size);

  virtual ~Intention();

  void add_plan(Plan plan);

  bool stack_plan(Plan plan);

  bool run_intention(BeliefBase beliefs, EventBase events);

  bool is_finished() const;
};

#endif /* BDI_INTENTION_H_ */