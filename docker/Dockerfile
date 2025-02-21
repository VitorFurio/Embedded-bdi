
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
    && rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/VitorFurio/Embedded-bdi.git

CMD ["sh", "-c", "git -C /Embedded-bdi pull && exec bash"]


