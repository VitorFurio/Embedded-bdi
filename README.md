This is an example of communication between embedded bdi agents using the MQTT protocol and the .broadcast internal action.
This example consists of a conversation between Agent Bob and Agent Alice.

Before running this example install the MQTT library Paho, necessary for communication: [https://github.com/eclipse/paho.mqtt.cpp].

Switch to the alice branch:
```sh
git switch alice
```
Compile Agent alice:
```sh
make agent
```
and run the agent:
```sh
./build/agent.out
```

In another terminal, switch to the bob branch:
```sh
git switch bob
```
and compile and run the agent:
```sh
make agent
./build/agent.out
```

Bob's output should be:
```
Hello, I'm Bob!!
Message arrived on topic "broadcast": ACHIEVE/hello
Message arrived on topic "broadcast": ACHIEVE/is_day
It's night now, Alice.
Message arrived on topic "broadcast": TELL/its_night
```
and Alice's:
```
Hey, I'm Alice and I'm running...

Message arrived on topic "broadcast": ACHIEVE/hello
Hello Bob, I'm Alice!
Is it day or night now?
Message arrived on topic "broadcast": ACHIEVE/is_day
Message arrived on topic "broadcast": TELL/its_night
Meh, it's night, I'm going to sleep...
```
