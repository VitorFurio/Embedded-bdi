// belief_1.
// belief_2.

// !goal_1.
// !goal_2.

// +belief_plan <- action_1; +add_belief_1; -delete_belief_1; !add_goal_1.
// +!goal_plan : context_1 & context_2 <- action_2.

belief_1.

!goal_1.
!goal_4.
!goal_5.
!goal_6.

+!goal_1 : belief_1 <- action_1; !goal_2.
+!goal_2 <- action_2; +belief_1.
+belief_1 <- action_3; !goal_3.
+!goal_3 <- action_4; !goal_1.

+!goal_5 <- action_5; !goal_6.
+!goal_6 <- action_6; !goal_7.
+!goal_7 <- !goal_8.
+!goal_7 <- action_7; !goal_6.
+!goal_8 <- action_8.