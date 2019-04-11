#include <Arduino.h>
#include <LiquidCrystal.h>

char serial_message[64];
LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8, 9, 10, 11);

void setup() {
    Serial.begin(BAUD_RATE);
    lcd.begin(16,2);
    serial_message[0]='\0';
}

// the loop function runs over and over again forever
void loop() {
    // read from the serail input
    Serial.readBytesUntil('\n', serial_message, 64);
    // if a ackage has been read, print the content in the lcd
    if (serial_message[0] != '\0'){
        // clears the lcd display
        lcd.setCursor(0,0);
        for (size_t i = 0; i < 16*2; i++) {
            lcd.print(" ");
        }
        
        // prints the content of serial_message
        lcd.setCursor(0,0);
        lcd.print(serial_message);
        
        // clears the serial message
        serial_message[0]='\0';
    }
}