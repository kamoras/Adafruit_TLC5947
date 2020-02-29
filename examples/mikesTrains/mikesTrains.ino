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
    randomChange(); 
    delay(10000);
}


// Fill the dots one after the other with a color
void lightsOn() {
  for(uint16_t i=0; i<24*NUM_TLC5974; i++) {
      tlc.setPWM(i, 4095);
      tlc.write();
  }
}

void lightsOff() {
  for(uint16_t i=0; i<24*NUM_TLC5974; i++) {
      tlc.setPWM(i, 0);
      tlc.write();
  }
}

void randomChange() {
  bool randbool;
  for(uint16_t i=0; i<24*NUM_TLC5974; i++) {
      randbool = rand() & 1;
      if (randbool) {
        tlc.setPWM(i, 4095);
      }
      else {
        tlc.setPWM(i, 0);
      }
  }
  tlc.write();
}
