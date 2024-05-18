// Agent Bob.

!start.
its_night.
!is_day. 

+!start <- .broadcast(achieve,hello).

+!hello <- say_hello.

+!is_day <- .broadcast(tell,its_night).


