#!/usr/bin/python3
'''
This file is part of the Pancho, A Non Conventional House Online project
www.github.com/riera90/Pancho

Licenced under BSD 3

Authors:
    Diego Rodríguez Riera (riera90)


This script is the alarm module of Pancho
It Load the alarms from a XML file and sends commands to the speakers module while accepting commands from the
nightstand module for snoozing and stopping the alarm.


Requirements (modules)
    MQTT Broker
    Speakers
    Nightstand display
'''

import time
from datetime import datetime, timedelta
import xml.etree.ElementTree as ET
import paho.mqtt.client as mqtt

from pprint import pprint

################################################################################
# Configuration
################################################################################

ALARMS_XML = "alarms.xml"
SNOOZ_TIME = timedelta(seconds=10)
ALARM_MUSIC = "music.flac"

HOSTNAME = "alarm"
MQTT_BROKER = "localhost"
MQTT_BROKER_PORT = 7707
MQTT_USERNAME = "admin"
MQTT_PASSWORD = "admin"
MQTT_TOPIC_NIGHTSTAND_BUTTON = "/nightstand/button"
MQTT_TOPIC_SPEAKERS = "/speakers"
MQTT_QOS = 0

################################################################################
# Beginning of script
################################################################################

next_alarm = None
alarm_is_ringing = False

# sets up the MQTT client
mqtt_client = mqtt.Client(HOSTNAME)
mqtt_client.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)
mqtt_client.connect(MQTT_BROKER, MQTT_BROKER_PORT)
mqtt_client.subscribe(MQTT_TOPIC_NIGHTSTAND_BUTTON, MQTT_QOS)


# Define event callbacks
def on_connect(client, userdata, flags, rc):
    print("rc: " + str(rc))

def on_message(client, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    global alarm_is_ringing

    request = msg.payload.decode("utf-8")
    if request == 'hold':
        print("stopping the alarm")
        alarm_is_ringing = False
        mqtt_client.publish(MQTT_TOPIC_SPEAKERS, 'stop', MQTT_QOS)
    if request == 'press':
        print("snoozing the alarm")
        mqtt_client.publish(MQTT_TOPIC_SPEAKERS, 'stop', MQTT_QOS)

def on_publish(client, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_log(client, obj, level, string):
    print(string)

# Assign event callbacks
mqtt_client.on_message = on_message
mqtt_client.on_connect = on_connect
mqtt_client.on_publish = on_publish
mqtt_client.on_subscribe = on_subscribe


def time_plus(time, timedelta):
    dummy_date = datetime.today()
    full_datetime = datetime.combine(dummy_date, time)
    added_datetime = full_datetime + timedelta
    return added_datetime.time()


def time_minus(time, timedelta):
    dummy_date = datetime.today()
    full_datetime = datetime.combine(dummy_date, time)
    added_datetime = full_datetime - timedelta
    return added_datetime.time()


def get_next_alarm_for_today():
    '''
    Gets the next alarm (from the XML) of the actual day
    :return: time / None
    '''
    tree = ET.parse(ALARMS_XML)
    root = tree.getroot()
    alarms = root.findall('alarm')

    today_alarms = []
    # from all the alarms
    for alarm in alarms:
        # get today's alarms
        if int(alarm.find('day').text) == datetime.now().weekday():
            today_alarms.append(alarm)

    # remove the already rang alarms
    for alarm in today_alarms:
        alarm_time = datetime.strptime(alarm.find('time').text, "%H:%M:%S").time()
        if alarm_time <= datetime.now().time():
            today_alarms.remove(alarm)

    # get the next alarm
    next_alarm = None
    for alarm in today_alarms:
        alarm_time = datetime.strptime(alarm.find('time').text, "%H:%M:%S").time()
        if next_alarm == None or alarm_time <= datetime.strptime(next_alarm.find('time').text, "%H:%M:%S").time():
            next_alarm = alarm

    # return the next alarm for the day
    if next_alarm is None:
        return None
    else:
        return next_alarm


def ring_alarm():
    '''
    rings the mqtt alarm until the alarm is stopped or it timeouts
    '''
    print("ring rang rung!")
    global alarm_is_ringing
    alarm_is_ringing = True

    last_ring = datetime.now().time()

    mqtt_client.publish(MQTT_TOPIC_SPEAKERS, "play "+ALARM_MUSIC, MQTT_QOS)

    while alarm_is_ringing:
        try:
            mqtt_client.loop()
            if time_plus(last_ring, SNOOZ_TIME) < datetime.now().time():
                mqtt_client.publish(MQTT_TOPIC_SPEAKERS, "play "+ALARM_MUSIC, MQTT_QOS)
                last_ring = datetime.now().time()
        except Exception as e:
            print(e)

    mqtt_client.publish(MQTT_TOPIC_SPEAKERS, "stop", MQTT_QOS)





def alarm_pooling():
    '''
    pooling of the alarm
    '''
    global next_alarm

    if not next_alarm:
        next_alarm = get_next_alarm_for_today()
        if not next_alarm:
            print("there is no alarm")
            return

    print(datetime.strptime(next_alarm.find('time').text, "%H:%M:%S").time())

    # the time of the alarm has come
    if datetime.strptime(next_alarm.find('time').text, "%H:%M:%S").time() <= datetime.now().time():
        # rings the alarm
        ring_alarm()
        next_alarm = get_next_alarm_for_today()


def main():
    print(get_next_alarm_for_today())

    while True:
        try:
            alarm_pooling()
            time.sleep(0.5)

        except Exception as e:
            print(e)


if __name__ == "__main__":
    main()


################################################################################
# End of script
################################################################################