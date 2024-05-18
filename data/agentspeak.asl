// Agent Bob.

!start.

//!is_day. 

its_night. // Bob needs to have its_night proposition to send it to Alice
hello. // Bob needs to have hello proposition(in belief, intention or plan) to send it to Alice

+!start <- say_hello; .broadcast(achieve,hello).

+!is_day <- .broadcast(tell,its_night). // bob doesn't need to have the is_day intention he just need have a plan to deal with it.
