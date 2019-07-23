FROM eclipse-mosquitto:latest

COPY ./mosquitto.conf /mosquitto/config/mosquitto.conf

COPY ./passwd /mosquitto/passwd

# RUN mkdir -p /mosquitto/log \
        # && chown -R mqtt /mosquitto/log
        
VOLUME "/mosquitto/log"

RUN mosquitto_passwd -U /mosquitto/config/mosquitto.conf

# USER mqtt

CMD mosquitto -c /mosquitto/config/mosquitto.conf

