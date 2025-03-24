
# To generate the image and push to dockerhub, type ./create_image.sh <version>. 
# The target repository is at https://hub.docker.com/repository/docker/maiquelb/embedded-bdi/general

FROM ubuntu:latest

RUN apt update && apt install -y \
    git \
    cmake \
    openjdk-21-jdk \
    g++ \
    libpaho-mqtt-dev \
    libpaho-mqttpp-dev \
    wget \
    flex \ 
    bison \
    gperf \
    python3 \  
    python3-pip \
    python3-venv \
    cmake \
    ninja-build \
    ccache \
    libffi-dev \
    libssl-dev \
    dfu-util \
    libusb-1.0-0 \
    nano
    
    
# requirements for ESP32    
RUN rm -rf /var/lib/apt/lists/* &&\
    mkdir -p ~/esp &&\
    cd ~/esp &&\
    git clone -b v5.2.5 --recursive https://github.com/espressif/esp-idf.git  &&\
    cd ~/esp/esp-idf &&\
   ./install.sh esp32 


# requirements for ESP8288
RUN mkdir -p ~/esp &&\
    cd ~/esp &&\
    wget https://dl.espressif.com/dl/xtensa-lx106-elf-gcc8_4_0-esp-2020r3-macos.tar.gz &&\
    tar -xzf xtensa-lx106-elf-gcc8_4_0-esp-2020r3-macos.tar.gz &&\         
    git clone --recursive https://github.com/espressif/ESP8266_RTOS_SDK.git &&\
    echo 'pip install virtualenv && export PATH="$PATH:$HOME/esp/xtensa-lx106-elf/bin" && export IDF_PATH=/root/esp/ESP8266_RTOS_SDK && cd $IDF_PATH && ./install.sh && source ./export.sh' > /setup_esp8266.sh &&\
    chmod +x /setup_esp8266.sh

RUN git clone https://github.com/VitorFurio/Embedded-bdi.git &&\
    git clone https://github.com/VitorFurio/nodemcuv3-embedded-bdi.git &&\
    git clone https://github.com/VitorFurio/Embedded-BDI_ESP32.git

RUN cp -r /nodemcuv3-embedded-bdi/embedded-bdi/lib /Embedded-BDI_ESP32/embedded-bdi/lib
RUN sed -i '/^flash:/a IDF_EXTRA_LDFLAGS="-L/usr/local/lib -lpaho-mqtt3as" \\' /Embedded-BDI_ESP32/Makefile
RUN sed -i '/^flash:/a IDF_EXTRA_LDFLAGS="-L/usr/local/lib -lpaho-mqtt3as" \\' /Embedded-BDI_ESP32/Makefile
RUN sed -i 's|^interface=/dev/ttyUSB1$|interface=/dev/ttyUSB0|' /Embedded-BDI_ESP32/Makefile 
RUN echo '. $HOME/esp/esp-idf/export.sh' >> ~/.bashrc



CMD ["sh", "-c", "git -C /Embedded-bdi pull && git -C /nodemcuv3-embedded-bdi pull && git -C /Embedded-BDI_ESP32 pull && source ~/.bashrc && exec bash"]


