#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#define STASSID "2 pi 1 net"
#define STAPSK  "d|Ewl+k5>~rucFipo~&lj!.v+pcq\"7"
#define HOSTNAME "nightstand ESP"
#define NODE_NAME "nightstand"
#define MQTT_BROKER "192.168.100.100"
#define MQTT_BROKER_PORT 7707
#define BAUD_RATE 9600
#define BUFFER_LENGTH 255

#define MQTT_USERNAME "admin"
#define MQTT_PASSWORD "admin"
#define MQTT_TOPIC "/test"
#define MQTT_QOS 1

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
String buffer;
int status = WL_IDLE_STATUS;
int counter = 0;


/**
 * wakes up the ATMega and lcd display
 */
void wake_up_atmega()
{
    counter = 0;
    digitalWrite(2, HIGH);
    delay(1000);
}


/**
 * displays a formated text into the lcd display
 * |n is accepted and |0 is requiered at the end of the input
 */
void display_on_lcd(String payload)
{
    wake_up_atmega();
    Serial.print(payload.length());
    for (unsigned int i = 0; i < payload.length(); i++) {
        Serial.print(payload[i]);
    }
}


/**
 * resets the board
 */
void reset()
{
    delay(5000);
    display_on_lcd("reseting board\0");
    while (true); // reset the board (watchdog kicks in)
}


/**
 * sets the ATMega and lcd display to sleep
 */
void sleep_atmega()
{
    display_on_lcd("going to sleep\0");
    delay(2000);
    digitalWrite(2, LOW);
}




void setup() {
    // sets the gpio to their modes 0 for the button and 2 for the transistors
    pinMode(2, OUTPUT); 
    pinMode(0, INPUT);
    // enables the LCD and ATMega (similar to wake_up_atmega function)
    digitalWrite(2, HIGH);
    
    // sets up the serial connection for the ATMega
    Serial.begin(BAUD_RATE);
    
    // sets up the WiFi connection
    WiFi.hostname(HOSTNAME);
    WiFi.begin(STASSID, STAPSK);
    
    // checks if the ESP is connected to the network, if not, wait until it is
    for (int i = 0; WiFi.status() != WL_CONNECTED; i++) {
        if (i > 1000) { // 10000 ns if after 10 seconds if it si not connected
            buffer = String("couldn't connect\nto ")+String(STASSID);    
            display_on_lcd(buffer);
            reset();
        }
        delay(10);
    }
    
    // display what the ESP hostname is and where is connected
    buffer = String(HOSTNAME)+"\nat "+String(STASSID);
    display_on_lcd(buffer);
    
    // connect to the mqtt broker
    mqttClient.connect(HOSTNAME, MQTT_USERNAME, MQTT_PASSWORD);
    mqttClient.subscribe (MQTT_TOPIC, MQTT_QOS);
    mqttClient.setServer(MQTT_BROKER,MQTT_BROKER_PORT);
    for (int i = 0; mqttClient.connected() != 0; i++) {
        if (i > 1000) { // 10000 ns if after 10 seconds if it si not connected
            buffer = String("couldn't connect\nto MQTT broker");    
            display_on_lcd(buffer);
            reset();
        }
        delay(10);
    }
    
    display_on_lcd("Connected to\nMQTT broker");
    
    display_on_lcd("All Systems Go");
    
}


void loop()
{
    // sleep algorithm
    
    // each 3 ns increment the counter if the system is fully awake
    delay(3);
    // if the ATMega is sending information, it is doing things so don't send it to sleep
    if (Serial.available() > 0) {
        // clear the buffer, sets the counter co zero and continue pooling.
        Serial.read();
        counter = 0;
    }
    else{
        // if it is not sending, it is doing nothing, suspend at 30 secconds (30000ns)
        if (counter < 10000) {
            counter++;
        }else{
            if (counter == 10000) {
                sleep_atmega();
                counter++;
            }
        }
    }
    
    // do the cool stuff
    mqttClient.publish("/test","hi from esp!");
    
}