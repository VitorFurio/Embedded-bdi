// Agent Alice.

!start.
!is_day. //Ask Bob if it's day
its_day. 
its_night.

+!start <- say_start.

+!hello <- say_hello .broadcast(achieve,is_day).

+its_day <- say_its_day.
+its_night <- say_its_night.
