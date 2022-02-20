/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

/***************************************************
 * Code works for two capacitive sensors
 */

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t last_pin_touched = 0;
uint16_t current_pin_touched = 0;
uint16_t last_pin_touched2 = 0;
uint16_t current_pin_touched2 = 0;
//bool six_touched = false;

void setup() {
  Serial.begin(9600);

  while (!Serial) { 
    // delay keeps Nano from starting too fast
    delay(10);
  } 
  
  if (!cap.begin(0x5A)) {
    Serial.println("0x5A - touch sensor is not connected correctly");
    while (1);
  }
  Serial.println("0x5A - touch sensor is working");
  
  if (!cap2.begin(0x5C)) {
    Serial.println("0x5C - touch sensor is not connected correctly");
    while (1);
  }
  Serial.println("0x5C - touch sensor is working");

  // Adjust the sensitivity
  uint8_t touch_threshold = 12
  uint8_t release_threshold = 6
  setThresholds(touch_threshold, release_threshold)
}

void loop() {
  // Get the currently touched pins
  current_pin_touched = cap.touched();
  current_pin_touched2 = cap2.touched();
  
  for (uint8_t i=0; i<12; i++) {
    if ((current_pin_touched & _BV(i)) && !(last_pin_touched & _BV(i)) ) {
      Serial.print("A "); Serial.print(i); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched & _BV(i)) && (last_pin_touched & _BV(i)) ) {
      Serial.print("A "); Serial.print(i); Serial.print(" "); Serial.println(false);
    }
    
    if ((current_pin_touched2 & _BV(i)) && !(last_pin_touched2 & _BV(i)) ) {
       Serial.print("C "); Serial.print(i); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched2 & _BV(i)) && (last_pin_touched2 & _BV(i)) ) {
      Serial.print("C "); Serial.print(i); Serial.print(" "); Serial.println(false);
    }
  }

  // reset our state
  last_pin_touched = current_pin_touched;
  last_pin_touched2 = current_pin_touched2;

  return;
}
