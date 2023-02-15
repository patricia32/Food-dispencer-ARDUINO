/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output26State = "off";
String output27State = "off";

// Assign output variables to GPIO pins
const int output26 = 26;
const int output27 = 27;


// leds
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 16 // Popular NeoPixel ring size
#include <Adafruit_NeoPixel.h>
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//RTC
#include "RTClib.h"
RTC_DS3231 rtc;

//servo
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <Servo.h>
Servo myservo; 
int pos = 0; 

void setup() {

    //SERVO
  myservo.attach(13);

  //RTC
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  rtc.adjust(DateTime(__DATE__, __TIME__));


  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output26, OUTPUT);
  pinMode(output27, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output26, LOW);
  digitalWrite(output27, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();

  //PIXEL
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(9600);
 
  delay(500);
}

void loop(){

   DateTime now = rtc.now();
    if(now.second() == 0){
      pixels.setPixelColor(0, pixels.Color(120,0,39));
      pixels.setPixelColor(1, pixels.Color(120,0,39));
      pixels.setPixelColor(2, pixels.Color(120,0,39));
      pixels.setPixelColor(3, pixels.Color(120,0,39));
      pixels.setPixelColor(4, pixels.Color(120,0,39));
      pixels.setPixelColor(5, pixels.Color(120,0,39));
      pixels.setPixelColor(6, pixels.Color(120,0,39));
      pixels.setPixelColor(7, pixels.Color(120,0,39));
      pixels.setPixelColor(8, pixels.Color(120,0,39));
      pixels.setPixelColor(9, pixels.Color(120,0,39));
      pixels.setPixelColor(10, pixels.Color(120,0,39));
      pixels.setPixelColor(11, pixels.Color(120,0,39));
      pixels.setPixelColor(12, pixels.Color(120,0,39));
      pixels.setPixelColor(13, pixels.Color(120,0,39));
      pixels.setPixelColor(14, pixels.Color(120,0,39));
      pixels.setPixelColor(15, pixels.Color(120,0,39));
      pixels.show();

      for (pos = 0; pos <= 120; pos +=2) {
        myservo.write(pos); 
        delay(15);            
       }
        for (pos = 120; pos >= 0; pos -= 2) {  
        myservo.write(pos);
        delay(15); 
        }
    }
    pixels.clear();
    pixels.show();


  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              pixels.setPixelColor(0, pixels.Color(120,0,39));
              pixels.setPixelColor(1, pixels.Color(120,0,39));
              pixels.setPixelColor(2, pixels.Color(120,0,39));
              pixels.setPixelColor(3, pixels.Color(120,0,39));
              pixels.setPixelColor(4, pixels.Color(120,0,39));
              pixels.setPixelColor(5, pixels.Color(120,0,39));
              pixels.setPixelColor(6, pixels.Color(120,0,39));
              pixels.setPixelColor(7, pixels.Color(120,0,39));
              pixels.setPixelColor(8, pixels.Color(120,0,39));
              pixels.setPixelColor(9, pixels.Color(120,0,39));
              pixels.setPixelColor(10, pixels.Color(120,0,39));
              pixels.setPixelColor(11, pixels.Color(120,0,39));
              pixels.setPixelColor(12, pixels.Color(120,0,39));
              pixels.setPixelColor(13, pixels.Color(120,0,39));
              pixels.setPixelColor(14, pixels.Color(120,0,39));
              pixels.setPixelColor(15, pixels.Color(120,0,39));
              pixels.show();

              for (pos = 0; pos <= 120; pos +=2) { 
                myservo.write(pos);
                delay(15);      
              }

              for (pos = 120; pos >= 0; pos -= 2) {
                myservo.write(pos); 
                delay(15); 
              }
             pixels.clear();
             pixels.show();
             output26State = "off";
            }
             if (header.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              pixels.clear();
              pixels.show();
            }
            
     
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Dispenser Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>GPIO 26 - State " + output26State + "</p>");
            // If the output26State is off, it displays the ON button       
            if (output26State=="off") {
              client.println("<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 

            
            // Display current state, and ON/OFF buttons for GPIO 27  
            client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            if (output27State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";

    
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}