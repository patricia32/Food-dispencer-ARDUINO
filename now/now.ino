// now.pde
// Prints a snapshot of the current date and time along with the UNIX time
// Modified by Andy Wickert from the JeeLabs / Ladyada RTC library examples
// 5/15/11

#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <Servo.h>

Servo myservo; 
RTC_DS3231 rtc;
int pos = 0; 

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        14 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 16 // Popular NeoPixel ring size
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup () {
  //SERVO
  myservo.attach(13);


  //RTC
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif


  //PIXEL
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
    Serial.begin(9600);
    Wire.begin();
    delay(500);
    Serial.println("Nano Ready!");
    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }

  rtc.adjust(DateTime(__DATE__, __TIME__));
}
void loop () {
        

    DateTime now = rtc.now();
    if(now.second() % 10 == 0){
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

      for (pos = 0; pos <= 120; pos +=2) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(15);            // waits 15ms for the servo to reach the position
       }
        for (pos = 120; pos >= 0; pos -= 2) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
        myservo.write(pos);  // tell servo to go to position in variable 'pos'
        delay(15);            // waits 15ms for the servo to reach the position
        }
    
     // delay(3000);
    }


    pixels.clear();
    pixels.show();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    

}
