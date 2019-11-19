#include <Arduino.h>
#include "LiquidCrystal.h"

#define BAUD_RATE 9600

int size;
bool scroll;
char buffer[64];
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup() {
    Serial.begin(BAUD_RATE);
    lcd.begin(16,2);
    size = 0;
}

// the loop function runs over and over again forever
void loop() {
    // read from the serail input
    size = Serial.parseInt();
    // if a package has been read, print the content in the lcd
    if (size > 0)
    {
        Serial.print("working");
        
        // clears the lcd display
        lcd.clear();
        // reads the given size of the string from the serial buffer and stores
        // it into the buffer variable
        Serial.readBytes(buffer, size);
    
        scroll = false;
    
        // prints the content of the given message
        for (size_t i = 0, j = 0; i < size; i++, j++) {
            // if a newline is entered, change the cursor to the 2nd line
            if (buffer[i] == '\n') {
                lcd.setCursor(0,1);
                j = 0;
            }
            else{
                // if there is more than 16 characters in a line,
                // enable scroll mode
                if (j == 16){
                    scroll = true;
                }
                lcd.print(buffer[i]);
            }
        }
    
        // delay 5 seconds between texts, activating scroll if there is
        for (size_t i = 0; i < 10; i++) {
            if (i == 0){
                delay(1000);
                i += 2;
            }
            if (scroll) {
                lcd.scrollDisplayLeft();
            }
            delay(500);
        }
    }
}