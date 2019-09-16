#!/usr/bin/python3

import time
from datetime import datetime, timedelta
import xml.etree.ElementTree as ET
import paho.mqtt.client as mqtt
import config


next_alarm = None
repeat_counter = 0
ringing = False
active_alarm = False

# sets up the MQTT client
mqtt_client = mqtt.Client(config.HOSTNAME)
mqtt_client.username_pw_set(config.MQTT_USERNAME, config.MQTT_PASSWORD)
mqtt_client.connect(config.MQTT_BROKER, config.MQTT_BROKER_PORT)
mqtt_client.subscribe(config.MQTT_TOPIC_NIGHTSTAND_BUTTON, config.MQTT_QOS)


class Alarm():
    def __init__(self, datetime=None, message=""):
        self.__message = message
        self.__datetime = datetime

    def getDatetime(self):
        return self.__datetime

    def setDatetime(self, datetime=None):
        self.__datetime = datetime
        return self

    def getMessage(self):
        return self.__message


def stop_alarm():
    '''
    stops the alarm, sending a stop signal to the speakers and stops the snooze functionality
    '''
    global repeat_counter
    global next_alarm
    global ringing
    global active_alarm

    if active_alarm is True:
        print("stopping the alarm")
        repeat_counter = 0
        next_alarm = None
        mqtt_client.publish(config.MQTT_TOPIC_SPEAKERS, 'stop', config.MQTT_QOS)
        mqtt_client.publish(config.MQTT_TOPIC_NIGHTSTAND_LCD, next_alarm.getMessage(), config.MQTT_QOS)
        active_alarm = False
        ringing = False
        # the lights will be turned off by the nightstand  when the button is pressed

def snooze_alarm():
    '''
    snoozes the alarm, sending a stop signal to the speakers and letting the snooze functionality do its job
    '''
    global ringing
    
    if ringing is True:
        print("snoozing the alarm")
        mqtt_client.publish(config.MQTT_TOPIC_SPEAKERS, 'stop', config.MQTT_QOS)
        ringing = False


# Define event callbacks
def on_connect(client, userdata, flags, rc):
    print("rc: " + str(rc))

def on_message(client, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))

    request = msg.payload.decode("utf-8")
    if request == 'hold':
        stop_alarm()
    if request == 'press':
        snooze_alarm()

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


def get_formatted_alarms():
    '''
    Gets the alarms (from the XML)
    :return: datetime array / None
    '''
    tree = ET.parse(config.ALARMS_XML)
    root = tree.getroot()
    alarms = root.findall('alarm')

    formatted_alarms = []
    # builds the datetime from the xml for ease of comparision
    today = datetime.today()
    for alarm in alarms:
        alarm_time = datetime.strptime(alarm.find('time').text, "%H:%M:%S")
        formatted_alarm = datetime(year=today.year,
                                   month=today.month,
                                   day=today.day,
                                   hour=alarm_time.hour,
                                   minute=alarm_time.minute,
                                   second=alarm_time.second)
        days_difference = (int)(alarm.find('day').text) - today.weekday()
        if days_difference is 0: # the alarm is the same day as today
            if datetime.strptime(alarm.find('time').text, "%H:%M:%S").time() <= datetime.now().time(): # the alarm has passed
                days_difference = 7
            else: # the alarm is today and it has not passed yet
                days_difference = 0
        else:
            if days_difference < 0: # the alarm is in next week
                # 0 1 2 3 4 5 6
                # a           t
                # days = 0 - 6 = -6
                # days_diff = 7 + (- 6) = 1
                days_difference = 7 + days_difference

            # else: the alarm is this week, useless for program but useful for programmer, so commented
                # 0 1 2 3 4 5 6
                #     t       a
                # days = 6 - 2 = 4
                # days_diff = 4
                # days_difference = days_difference

        difference = timedelta(days=days_difference)
        formatted_alarm = formatted_alarm + difference

        # creates and saves the alarm in the formatted alarms
        message = (alarm.find('message').text)
        formatted_alarms.append(Alarm(formatted_alarm, message))

    return formatted_alarms


def get_next_alarm():
    '''
    gets the next alarm from the returned by get_formatted_alarms function
    :return: datetime
    '''
    alarms = get_formatted_alarms()
    next_alarm = alarms[0]
    for alarm in alarms:
        if alarm.getDatetime() < next_alarm.getDatetime():
            next_alarm = alarm
    return next_alarm


def ring_alarm():
    '''
    rings the mqtt alarm until the alarm is stopped or it timeouts
    '''
    global repeat_counter
    global next_alarm
    global ringing
    global active_alarm
    
    ringing = True
    active_alarm = True
    repeat_counter += 1
    print("ringing alarm:", next_alarm.getDatetime())
    print("repaet no", repeat_counter)
    mqtt_client.publish(config.MQTT_TOPIC_SPEAKERS, "play " + config.ALARM_MUSIC, config.MQTT_QOS)

    if repeat_counter >= config.REPEAT_NUMBER: # the repeat counter has been already reached, canceling snooze functionality
        next_alarm = None
        repeat_counter = 0
        print("EOA")
        return

    next_alarm.setDatetime(next_alarm.getDatetime() + config.SNOOZE_TIME)
    print("new snooze set to:", next_alarm.getDatetime())

    # turns on the lights
    mqtt_client.publish(config.MQTT_TOPIC_LED_STRIP_SOFTWARE_STATION, "1024,1024,1024", config.MQTT_QOS)

    return

def alarm_pooling():
    '''
    pooling of the alarm
    '''
    global next_alarm

    if not next_alarm:
        next_alarm = get_next_alarm()
        if not next_alarm:
            print("there is no alarms in the xml file or the format is wrong")
            return
        print("next alarm set at:", next_alarm.getDatetime())

    # the time of the alarm has come
    if next_alarm.getDatetime() <= datetime.now():
        # rings the alarm
        ring_alarm()
    return



def main():
    while True:
        try:
            mqtt_client.loop()
            alarm_pooling()
            time.sleep(1)
        except Exception as e:
            print(e)


if __name__ == "__main__":
    main()