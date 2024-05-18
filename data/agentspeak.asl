// Agent Alice.

!start.
is_day. //agents only send beliefs and goals that they themselves have. 

+!start <- .broadcast(achieve,hello).

+!hello <- say_hello .broadcast(achieve,is_day).

//+happy <- .broadcast(achieve,hello).


