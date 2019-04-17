#include <Arduino.h>
#include "LiquidCrystal.h"

#define BAUD_RATE 9600

int size;
bool scroll;
char buffer[64];
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
    Serial.begin(BAUD_RATE);
    lcd.begin(16,2);
    lcd.print("hi from Pancho!");
    lcd.setCursor(0,1);
    lcd.print("waking up...");
    size = 0;
}

// the loop function runs over and over again forever
void loop() {
    // read from the serail input
    if (scroll) {
        lcd.scrollDisplayLeft();
    }
    delay(500);
    
    size = Serial.parseInt();
    // if a package has been read, print the content in the lcd
    if (size > 0){
        // clears the lcd display
        lcd.clear();
        // reads the given size of the string from the serial buffer and stores
        // it into the buffer variable
        Serial.readBytes(buffer, size);
    
        scroll = false;
    
        // prints the content of the given message
        for (int i = 0, j = 0; i < size; i++, j++) {
            // if a newline is entered, change the cursor to the 2nd line
            if (buffer[i] == '\n') {
                lcd.setCursor(0,1);
                j = 0;
            }
            else{
                // if there is more than 16 characters in a line, enable scroll mode
                if (j == 16){
                    scroll = true;
                }
                lcd.print(buffer[i]);
            }
        }
    }
}