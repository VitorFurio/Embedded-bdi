// file used to test translator
//+teste.

+test : test2 <- say_test.

-test2 <- .broadcast(achieve,happy).
!start.

+!start <- +happy.

+happy <- !!hello; .broadcast(achieve,happy).

+!hello <- say_hello.
-!hello <- say_test.
