![](https://github.com/Embedded-BDI/embedded-bdi/actions/workflows/unit-tests.yml/badge.svg) ![](https://github.com/Embedded-BDI/embedded-bdi/actions/workflows/gh-pages.yml/badge.svg)

Embedded-BDI allows programming deliberative [BDI](https://en.wikipedia.org/wiki/Belief%E2%80%93desire%E2%80%93intention_software_model) agents for embedded systems using [AgentSpeak](https://en.wikipedia.org/wiki/AgentSpeak)-like syntax.

Visit the [project page](https://embedded-bdi.github.io) for more information.

---
## Example
This example illustrates the communication between two agents. It can be run on a local installation or based on Docker containers (recommended).

### Local execution
First, install and build the mqtt paho library, in C code, asynchronous and unencrypted [paho-mqtt3a](https://github.com/eclipse/paho.mqtt.c)

Second, in a terminal compile and run the agent alice:
```sh
make alice
./build/agent.out
```
Third, in another terminal, compile and run the agent bob:
```sh
make bob
./build/agent.out
```
### Docker-based execution (recommended)
1. Run the container of agent <em>Alice</em>
```
docker run --rm maiquelb/embedded-bdi:latest /bin/bash -c "cd /Embedded-bdi && make alice && ./build/agent.out"
```
2. Run the container of agent <em>Bob</em>
```
docker run --rm maiquelb/embedded-bdi:latest /bin/bash -c "cd /Embedded-bdi && make bob && ./build/agent.out"
```
### Expected output

If communication between agents occurred successfully, Alice's output should be:
```
Hey, I'm Alice and I'm running...

Message arrived on topic broadcast: ACHIEVE/hello

Hello Everyone, I'm Alice!
[Question to Bob] Is it day or night now?
Sending message to topic bob: ACHIEVE/is_day
Message arrived on topic alice: TELL/its_night

Meh, it's night, I'm going to sleep...
```
and Bob's:
```
Hello, I'm Bob!!
Sending message to topic broadcast: ACHIEVE/hello
Message arrived on topic broadcast: ACHIEVE/hello
Message arrived on topic bob: ACHIEVE/is_day

It's night now, Alice.
Sending message to topic alice: TELL/its_night

```
Note: agent alice has to be executed first.

---

Version history

* v1.0.0 - [Matuzalem Muller dos Santos](https://matuzalemmuller.com)
