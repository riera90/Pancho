#include <Arduino.h>
#include <string.h>
#include <ESP8266WiFi.h>


#define STASSID "2 pi 1 net"
#define STAPSK  "d|Ewl+k5>~rucFipo~&lj!.v+pcq\"7"
#define HOSTNAME "nightstand ESP"
#define NODE_NAME "nightstand"
#define SERVER "192.168.100.149"
#define SERVER_PORT 7707
#define PORT 7708
#define BAUD_RATE 9600
#define ACK "OK"
#define BUFFER_LENGTH 255


WiFiServer server(PORT);
char buffer[BUFFER_LENGTH+1];
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
void display_on_lcd(const char* payload)
{
    wake_up_atmega();
    int size;
    for (size = 0; payload[size] != '\0' && size < 64; size++);
    Serial.print(size);
    for (int i = 0; i < size; i++) {
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
    Serial.print("14going to sleep\0");
    delay(2000);
    digitalWrite(2, LOW);
}


/**
 * Handles the command for the ESP
 */
const char* hanndle_command(const char* command)
{
    display_on_lcd(command);
    return ACK;
}


/**
 * sends a message to the server, server false is returned if it the ESP is
 * unable to connect or gets no response from him.
 * is returned, true is returned if the conenction was made and an ACK was 
 * recieved.
 */
std::string send_message_to_server(const char* payload)
{
    WiFiClient client;
    client.connect(SERVER, SERVER_PORT);
    // sends the payload to the server
    client.println(payload);
    
    // gets the server response into the buffer
    // clears the buffer
    bzero((char*) &buffer, sizeof(buffer)); 
    // waits for the tresponse
    for (int i = 0; !client.available(); i++){ 
        delay(5);
        if (i > 1000) // timeout at 5000 ns
            return "TIMEOUT"; 
    };
    // reads the response into buffer
    for (int i = 0; client.available() > 0; i++){
        buffer[i] = (char)client.read();
        buffer[i+1] = '\0';
    }
    // stops the client
    client.stop();
    // checks if the ACK is correct, if it is, return true, else return false
    return buffer;
}


/**
 * pooling method of the TCP/IP server at the ESP
 */
void tcp_server_pooling()
{
    // creates and ckecks if a client is connected
    WiFiClient client = server.available();
    if (client){
        // clears the buffer and write to it the request
        bzero((char*) &buffer, sizeof(buffer));
        for (int i = 0; client.available() > 0; i++){
            buffer[i] = (char)client.read();
            buffer[i+1] = '\0';
        }
        // handle the command and return the ACK or error message
        client.write(hanndle_command(buffer));
    }
}


/**
 * pooling method of the button at the ESP
 */
void button_press_pooling()
{
    if ( digitalRead(0) == LOW ){
        bzero((char*) &buffer, sizeof(buffer));
        strcat(buffer, "/");
        strcat(buffer, NODE_NAME);
        delay(800);
        if (digitalRead(0) == LOW ){
            strcat(buffer, "/button/hold");
        }
        else{
            strcat(buffer, "/button/press");
        }
        
        for (int i = 0; send_message_to_server(buffer) != "OK"; i++){
            if (i < 10){
                display_on_lcd("can't connect to\nspeakers\0");
                return;
            }
        }
        while (digitalRead(0) == LOW);//wait until the button is release
    }
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
            bzero((char*) &buffer, sizeof(buffer));
            strcat(buffer, "couldn't connect\nto ");
            strcat(buffer, STASSID);
            strcat(buffer, "\0");            
            display_on_lcd(buffer);
            reset();
        }
        delay(10);
    }
    
    // begin the server at the ESP
    server.begin();

    // display what the ESP hostname is and where is connected
    bzero((char*) &buffer, sizeof(buffer));
    strcat(buffer, HOSTNAME);
    strcat(buffer, "\nat ");
    strcat(buffer, STASSID);
    strcat(buffer, "\0");
    display_on_lcd(buffer);
    for (int i = 0; send_message_to_server("Hello") != "Hello"; i++){
        if (i < 10){
            bzero((char*) &buffer, sizeof(buffer));
            strcat(buffer, "can't connet to\n");
            strcat(buffer, SERVER);
            strcat(buffer, "\0");
            display_on_lcd(buffer);
            reset();
        }
    }
    display_on_lcd("All Systems Go");
}


void loop()
{
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
    
    // call both pooling funcitons
    tcp_server_pooling();
    button_press_pooling();
}