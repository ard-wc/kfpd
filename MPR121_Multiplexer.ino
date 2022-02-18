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

#define MULTIPLEXER_ADDRESS 0x70

void choose_multiplexer_port(uint8_t i) {
  if (i > 1) return;
 
  Wire.beginTransmission(MULTIPLEXER_ADDRESS);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Adafruit_MPR121 cap3 = Adafruit_MPR121();
Adafruit_MPR121 cap4 = Adafruit_MPR121();
Adafruit_MPR121 cap5 = Adafruit_MPR121();
Adafruit_MPR121 cap6 = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t last_pin_touched = 0;
uint16_t current_pin_touched = 0;
uint16_t last_pin_touched2 = 0;
uint16_t current_pin_touched2 = 0;
uint16_t last_pin_touched3 = 0;
uint16_t current_pin_touched3 = 0;
uint16_t last_pin_touched4 = 0;
uint16_t current_pin_touched4 = 0;
uint16_t last_pin_touched5 = 0;
uint16_t current_pin_touched5 = 0;
uint16_t last_pin_touched6 = 0;
uint16_t current_pin_touched6 = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { 
    // delay keeps Nano from starting too fast
    delay(10);
  } 

  // Set up the first three sensors on port 0 of multiplexer
  choose_multiplexer_port(0);
  if (!cap.begin(0x5A)) {
    Serial.println("0x5A Port 0 - touch sensor is not connected correctly");
    while (1);
  }
  Serial.println("0x5A Port 0 - touch sensor is working");

  if (!cap2.begin(0x5B)) {
    Serial.println("0x5B Port 0 - touch sensor is not connected correctly");
    while (1);
  }
  Serial.println("0x5B Port 0 - touch sensor is working");
  
  if (!cap3.begin(0x5C)) {
    Serial.println("0x5C Port 0 - touch sensor is not connected correctly");
    while (1);
  }
  Serial.println("0x5C Port 0 - touch sensor is working");

  // Set up the second three sensors on port 0 of multiplexer
  choose_multiplexer_port(1);
  if (!cap4.begin(0x5A)) {
    Serial.println("0x5A Port 1 - touch sensor is not connected correctly");
    while (1);
  }
  Serial.println("0x5A Port 1 - touch sensor is working");

  if (!cap5.begin(0x5B)) {
    Serial.println("0x5B Port 1 - touch sensor is not connected correctly");
    while (1);
  }
  Serial.println("0x5B Port 1 - touch sensor is working");
  
  if (!cap6.begin(0x5C)) {
    Serial.println("0x5C Port 1 - touch sensor is not connected correctly");
    while (1);
  }
  Serial.println("0x5C Port 1 - touch sensor is working");

  // Adjust the sensitivity
  uint8_t touch_threshold = 12
  uint8_t release_threshold = 6
  setThresholds(touch_threshold, release_threshold)
}

void loop() {
  // Get the currently touched pins
  current_pin_touched = cap.touched();
  current_pin_touched2 = cap2.touched();
  current_pin_touched3 = cap3.touched();
  current_pin_touched4 = cap4.touched();
  current_pin_touched5 = cap5.touched();
  current_pin_touched6 = cap6.touched();
  
  for (uint8_t i=0; i<12; i++) {
    choose_multiplexer_port(0);
    if ((current_pin_touched & _BV(i)) && !(last_pin_touched & _BV(i)) ) {
      Serial.print(i); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched & _BV(i)) && (last_pin_touched & _BV(i)) ) {
      Serial.print(i); Serial.print(" "); Serial.println(false);
    }
    
    if ((current_pin_touched2 & _BV(i)) && !(last_pin_touched2 & _BV(i)) ) {
       Serial.print(i+12); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched2 & _BV(i)) && (last_pin_touched2 & _BV(i)) ) {
      Serial.print(i+12); Serial.print(" "); Serial.println(false);
    }

    if ((current_pin_touched3 & _BV(i)) && !(last_pin_touched3 & _BV(i)) ) {
       Serial.print(i+24); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched3 & _BV(i)) && (last_pin_touched3 & _BV(i)) ) {
      Serial.print(i+24); Serial.print(" "); Serial.println(false);
    }

    choose_multiplexer_port(1);
    if ((current_pin_touched4 & _BV(i)) && !(last_pin_touched4 & _BV(i)) ) {
      Serial.print(i+36); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched4 & _BV(i)) && (last_pin_touched4 & _BV(i)) ) {
      Serial.print(i+36); Serial.print(" "); Serial.println(false);
    }
    
    if ((current_pin_touched5 & _BV(i)) && !(last_pin_touched5 & _BV(i)) ) {
       Serial.print(i+48); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched5 & _BV(i)) && (last_pin_touched5 & _BV(i)) ) {
      Serial.print(i+48); Serial.print(" "); Serial.println(false);
    }

    // we only need to check for one touch node to get to 61 keys
    if (i == 0 && (current_pin_touched6 & _BV(i)) && !(last_pin_touched6 & _BV(i)) ) {
       Serial.print(i+60); Serial.print(" "); Serial.println(true);
    }
    
    if (i == 0 && !(current_pin_touched6 & _BV(i)) && (last_pin_touched6 & _BV(i)) ) {
      Serial.print(i+60); Serial.print(" "); Serial.println(false);
    }
  }

  // reset our state
  last_pin_touched = current_pin_touched;
  last_pin_touched2 = current_pin_touched2;
  last_pin_touched3 = current_pin_touched3;
  last_pin_touched4 = current_pin_touched4;
  last_pin_touched5 = current_pin_touched5;
  last_pin_touched6 = current_pin_touched6;

  return;
}
