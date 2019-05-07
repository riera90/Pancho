FROM ubuntu:18.04
RUN apt update -y
RUN apt upgrade -y
RUN apt install -y mosquitto
COPY ./mqtt.conf /etc/mosquitto/mqtt.conf
RUN touch /etc/mosquitto/passwd
CMD mosquitto -c /etc/mosquitto/mqtt.conf 