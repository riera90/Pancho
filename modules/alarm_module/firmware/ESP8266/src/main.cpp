#include <Arduino.h>
#include <string.h>

#define BAUD_RATE 9600
bool status;


void send_message_serial(char* payload){
    int size;
    for (size = 0; payload[size] != '\0' && size < 64; size++);
    Serial.print(size);
    for (size_t i = 0; i < size; i++) {
        Serial.print(payload[i]);
    }
}

void setup() {
    
    Serial.begin(BAUD_RATE);
    pinMode(2, OUTPUT);
    status=true;
}

void loop() {
    // delay(10000);
    status = !status;
    digitalWrite(2, status);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    send_message_serial("hello from\npancho!\0");
    delay(1000);
    send_message_serial("this is a test\0");
    delay(1000);
    send_message_serial("this is a long message that should\nbe represented properly\0");
    delay(1000);
}