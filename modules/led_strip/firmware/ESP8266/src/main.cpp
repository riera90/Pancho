#define MQTT_VERSION 4

#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"



WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);


/**
 * resets the board
 */
void reset()
{
    delay(5000);
    Serial.print("reseting board\n");
    while (true); // reset the board (watchdog kicks in)
}


void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String buffer = "";
    for (size_t i = 0; i < length; i++) {
        buffer += (char)payload[i];
    }
    int red, green, blue;
    
    
    for (size_t i = 0; i < buffer.length(); i++) {
        if (buffer[i] == ',')
        {
            red = buffer.substring(0, i).toInt();
            buffer = buffer.substring(i+1);
            break;
        }
    }
    
    
    for (size_t i = 0; i < buffer.length(); i++) {
        if (buffer[i] == ',')
        {
            green = buffer.substring(0, i).toInt();
            buffer = buffer.substring(i+1);
            break;
        }
    }
    
    blue = buffer.toInt();
    
        
    analogWrite(RED, red);
    analogWrite(GREEN, green);
    analogWrite(BLUE, blue);
    
    
    Serial.print("\nstate:\n\tR:"+String(red)+"\n\tG:"+String(green)+"\n\tB:"+String(blue)+"\n");
}


void clean_leds()
{
    analogWrite(RED, 0);
    analogWrite(BLUE, 0);
    analogWrite(GREEN, 0); 
}

void delay_(){delay(1);}

void setup()
{
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
    clean_leds();
    
    Serial.begin(BAUD_RATE);
    
    
    WiFi.hostname(HOSTNAME);
    WiFi.begin(STASSID, STAPSK);
    
    // checks if the ESP is connected to the network, if not, wait until it is
    for (int i = 0; WiFi.status() != WL_CONNECTED; i++) {
        if (i > 1000) { // 10000 ns if after 10 seconds if it si not connected
            Serial.print(String("couldn't connect to ")+String(STASSID)+"\n");
            reset();
        }
        delay(10);
    }
    
    // display what the ESP hostname is and where is connected
    Serial.print(String(HOSTNAME)+" at "+String(STASSID)+"\n");
    
    // connect to the mqtt broker
    mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
    
    
    
    for (int i = 0; !mqttClient.connect(HOSTNAME, MQTT_USERNAME, MQTT_PASSWORD); i++) {
        if (i > 1000) { // 10000 ns if after 10 seconds if it is not connected
            Serial.print("couldn't connect to MQTT broker\n");
            reset();
        }
        delay(10);
    }
    Serial.print("Connected to MQTT broker\n");
    
    for (int i = 0; !mqttClient.subscribe(MQTT_TOPIC, MQTT_QOS); i++) {
        if (i > 1000) { // 10000 ns if after 10 seconds if it is not subscribed
            Serial.print("couldn't subscribe to the topic\n");    
            reset();
        }
        delay(10);
    }
    mqttClient.setCallback(mqtt_callback);
    
    Serial.print("All Systems Go\n");
}



void loop()
{
    // pooling for incomming messages at MQTT_TOPIC_SUB
    mqttClient.loop();
    
    if (!mqttClient.connected()) { // reconnect if not connected
        // wait untill connection
        for (int i = 0; !mqttClient.connect(HOSTNAME, MQTT_USERNAME, MQTT_PASSWORD); i++) {
            if (i > 1000) { // 10000 ns if after 10 seconds if it is not connected
                Serial.print("couldn't connect to MQTT broker\n");
                reset();
            }
            delay(10);
        }
    }
    
}