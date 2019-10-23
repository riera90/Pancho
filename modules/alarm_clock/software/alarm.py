#!/usr/bin/python3

import time
from datetime import datetime, timedelta
import xml.etree.ElementTree as ET
import paho.mqtt.client as mqtt
import requests
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


def get_meteo_report():
    '''
    Gets the meteorologic report from AEMET (spanish weather report agency)
    and returns a string to be displayed at the nightstand display
    (if available).

    This function output is in spanish, becouse it uses the AEMET api
    (witch data is in spanish)
    :return: string
    '''
    aemet_url = "https://opendata.aemet.es/opendata/api/prediccion/especifica/municipio/diaria/"+config.AEMET_MUNICIPE_CODE+"/?api_key="+config.AEMET_API_KEY
    response = requests.get(aemet_url)
    aemet_url = response.json()["datos"]
    response = requests.get(aemet_url)
    response = response.json()
    weather = response[0]['prediccion']['dia'][0]['estadoCielo'][0]['descripcion']
    if weather is "":
        weather = "soleado"

    rain = str(response[0]['prediccion']['dia'][0]['probPrecipitacion'][0]['value'])

    temp_min = str(response[0]['prediccion']['dia'][0]['temperatura']['minima'])
    temp_max = str(response[0]['prediccion']['dia'][0]['temperatura']['maxima'])

    return weather+", "+rain+"%\ntemp: "+temp_min+"/"+temp_max+" C"


def stop_alarm():
    '''
    Stops the alarm, sending a stop signal to the speakers and stops the snooze
    functionality
    '''
    global repeat_counter
    global next_alarm
    global ringing
    global active_alarm

    if active_alarm is True:
        print("stopping the alarm")
        repeat_counter = 0
        mqtt_client.publish(config.MQTT_TOPIC_SPEAKERS, 'stop', config.MQTT_QOS)
        mqtt_client.publish(config.MQTT_TOPIC_NIGHTSTAND_LCD, next_alarm.getMessage(), config.MQTT_QOS)
        next_alarm = None
        active_alarm = False
        ringing = False
        # the lights will be turned off by the nightstand  when the button is pressed


def snooze_alarm():
    '''
    snoozes the alarm, sending a stop signal to the speakers and letting the
    snooze functionality do its job
    '''
    global ringing
    global next_alarm

    if ringing is True:
        print("snoozing the alarm")
        mqtt_client.publish(config.MQTT_TOPIC_SPEAKERS, 'stop', config.MQTT_QOS)
        ringing = False
    mqtt_client.publish(config.MQTT_TOPIC_NIGHTSTAND_LCD, next_alarm.getMessage(), config.MQTT_QOS)
    mqtt_client.publish(config.MQTT_TOPIC_NIGHTSTAND_LCD, get_meteo_report(), config.MQTT_QOS)


# Define event callbacks
def on_connect(client, userdata, flags, rc):
    #print("rc: " + str(rc))
    pass

def on_message(client, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))

    request = msg.payload.decode("utf-8")
    if request == 'hold':
        stop_alarm()
    if request == 'press':
        snooze_alarm()

def on_publish(client, obj, mid):
    #print("mid: " + str(mid)
    pass

def on_subscribe(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_log(client, obj, level, string):
    #print(string)
    pass

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
            time.sleep(0.25)
        except Exception as e:
            print(e)


if __name__ == "__main__":
    main()
