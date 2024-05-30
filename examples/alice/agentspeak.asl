// Agent Alice.

!start.
!is_day. 
its_day. 
its_night.

+!start <- .my_name("alice"); say_start.

+!hello <- say_hello .send(bob,achieve,is_day). //Ask Bob if it's day

+its_day <- say_its_day.
+its_night <- say_its_night.
