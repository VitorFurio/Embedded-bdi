// Agent Bob.

!start.
//!is_day. 
its_night.

+!start <- .broadcast(achieve,hello).

+!hello <- say_hello.

+!is_day <- .broadcast(tell,its_night).
