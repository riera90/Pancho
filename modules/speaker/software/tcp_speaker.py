#!/usr/bin/python3

from pygame import mixer
import re, os, signal
import paho.mqtt.client as mqtt

################################################################################
############################### Configuration ##################################
################################################################################

HOSTNAME = "Speakers"
MQTT_BROKER = "localhost"
MQTT_BROKER_PORT = 7707
MQTT_USERNAME = "admin"
MQTT_PASSWORD = "admin"
MQTT_TOPIC = "/bedroom/speakers"
MQTT_QOS = 0

################################################################################
########################### end of Configuration ###############################
################################################################################


class Player():
    def __init__(self, path=""):
        self.__path = path
        self.__mixer = mixer
        self.__mixer.init()
        self.__vlc_pid = None
        self.__vlc_url = None

    def setPath(self, path):
        self.__path = path

    def play(self):
        self.__mixer.music.load(self.__path)
        self.__mixer.music.play()

    def stop(self):
        self.__mixer.music.stop()

    def pause(self):
        self.__mixer.music.pause()

    def resume(self):
        self.__mixer.music.unpause()

    def playWeb(self, url):
        if (self.__vlc_pid == None):
            self.__vlc_url = url
            self.__vlc_pid = os.fork()
            if self.__vlc_pid == 0:
                os.system("cvlc --intf dummy " + self.__vlc_url)
                os._exit(0)
        else:
            self.stopWeb()
            self.playWeb(url)

    def stopWeb(self):
        os.system("killall vlc -9")
        self.__vlc_pid = None


player = Player("music.flac")

mqtt_client = mqtt.Client(HOSTNAME)
mqtt_client.username_pw_set(MQTT_USERNAME, MQTT_PASSWORD)
mqtt_client.connect(MQTT_BROKER, MQTT_BROKER_PORT)
mqtt_client.subscribe(MQTT_TOPIC, MQTT_QOS)

# Define event callbacks
def on_connect(client, userdata, flags, rc):
    print("rc: " + str(rc))

def on_message(client, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))

    request = msg.payload.decode("utf-8")

    play_web = re.match(r'play web (.*)', request, re.I)
    if play_web:
        player.playWeb(play_web.group(1))


    play = re.match(r'play (.*)', request, re.I)
    if play:
        player.setPath(play.group(1))
        player.play()

    elif (request == "play"):
        player.play()

    elif (request == "pause"):
        player.pause()

    elif (request == "resume"):
        player.resume()

    elif (request == "stop"):
        player.stop()

    elif (request == "stop web"):
        player.stopWeb()


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






def main():
    while True:
        try:
            mqtt_client.loop()
        except Exception as e:
            print(e)


if __name__ == "__main__":
    main()
