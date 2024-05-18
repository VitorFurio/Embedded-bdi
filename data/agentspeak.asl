// Agent Bob.

!start.
its_night.
!is_day; -!is_day.

+!start <- .broadcast(achieve,hello).

+!hello <- say_hello.

+!is_day <- .boadcast(tell, its_night).
//+happy <- .broadcast(achieve,hello).


