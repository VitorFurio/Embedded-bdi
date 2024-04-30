// file used to test translator

!start.

+!start <- +happy.

+happy <- !!hello; .broadcast(tell,happy).

+!hello <- say_hello.
