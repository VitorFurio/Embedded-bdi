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


