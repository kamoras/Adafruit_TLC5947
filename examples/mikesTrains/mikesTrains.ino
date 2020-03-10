 /*************************************************** 
  This is an example for our Adafruit 24-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/1429

  These drivers uses SPI to communicate, 3 pins are required to  
  interface: Data, Clock and Latch. The boards are chainable

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_TLC5947.h"

// How many boards do you have chained?
#define NUM_TLC5974 1

#define data   4
#define clock   5
#define latch   6
#define oe  -1  // set to -1 to not use the enable pin (its optional)

Adafruit_TLC5947 tlc = Adafruit_TLC5947(NUM_TLC5974, clock, data, latch);

void setup() {
  Serial.begin(9600);
  
  Serial.println("TLC5974 test");
  tlc.begin();
  if (oe >= 0) {
    pinMode(oe, OUTPUT);
    digitalWrite(oe, LOW);
  }
}

void loop() {
    // This function is repeatedly executed
    // Change the function that goes in here to change functionality of the lights
    randomChangeOneLight();
    delay(5000); // Change this number to the wait in milliseconds between each light change
}

// Call this function in loop() to turn all the lights on
void lightsOn() {
  for(uint16_t i=0; i<24*NUM_TLC5974; i++) {
      tlc.setPWM(i, 4095); // Change the second number to change brightness of leds on scale from 0 to 4095
  }
  tlc.write();
}

// Call this function in loop() to turn all the lights off
void lightsOff() {
  for(uint16_t i=0; i<24*NUM_TLC5974; i++) {
      tlc.setPWM(i, 0);
  }
  tlc.write();
}

// Call this function in loop() to randomly turn 1 of your lights on or off.
void randomChangeOneLight() {
  int lightIndex = rand() % (24*NUM_TLC5974 - 1);
  bool randBool = rand() & 1;

  if (randBool) {
    tlc.setPWM(lightIndex, 4095); // Change the second number to change brightness of leds on scale from 0 to 4095
  }
  else {
    tlc.setPWM(lightIndex, 0);
  }

  tlc.write();
}

// Call this function in loop() to randomly change all the lights at once
void randomChange() {
  bool randbool;
  for(uint16_t i=0; i<24*NUM_TLC5974; i++) {
      randbool = rand() & 1;
      if (randbool) {
        tlc.setPWM(i, 4095); // Change the second number to change brightness of leds on scale from 0 to 4095
      }
      else {
        tlc.setPWM(i, 0);
      }
  }
  tlc.write();
}
