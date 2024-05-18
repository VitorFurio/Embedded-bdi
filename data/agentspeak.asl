// Agent Alice.

!start.
!is_day. //Ask Bob if it's day
its_day. 
its_night.

+!start <- .broadcast(achieve,hello).

+!hello <- say_hello .broadcast(achieve,is_day).

+its_day <- say_its_day.
+its_night <- say_its_night.


