// file used to test translator
//!test.

+test : test2 <- say_test.

+test <- .broadcast(tell,happy).
!start.

+!start <- +happy.

+happy <- !!hello; .broadcast(tell,test).

+!hello <- say_hello.
-!hello <- say_test.
