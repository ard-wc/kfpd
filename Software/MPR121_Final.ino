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
 * Works for six capacitive sensors
 */
// built in library for using I2C devices
#include <Wire.h>
#include "Adafruit_MPR121.h"
#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif
#define MULTIPLEXER_ADDRESS 0x70

void choose_multiplexer_port(uint8_t i)
{
  if (i <= 1)
  {
  Wire.beginTransmission(MULTIPLEXER_ADDRESS);
  Wire.write(1 << i);
  Wire.endTransmission();
  }
}

Adafruit_MPR121 cap = Adafruit_MPR121();
Adafruit_MPR121 cap2 = Adafruit_MPR121();
Adafruit_MPR121 cap3 = Adafruit_MPR121();
Adafruit_MPR121 cap4 = Adafruit_MPR121();
Adafruit_MPR121 cap5 = Adafruit_MPR121();
Adafruit_MPR121 cap6 = Adafruit_MPR121();

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

// Thresholds
uint8_t touch_threshold = 1;
uint8_t release_threshold = 1;

void setup()
{

  while (!Serial)
  { 
    // delay keeps Nano from starting too fast
    delay(10);
  } 

  Wire.begin();
  Serial.begin(9600);  

  // Set up the first three sensors on port 0 of multiplexer
  choose_multiplexer_port(0);
  if (cap.begin(0x5A))
  {
    Serial.println("0x5A Port 0 - touch sensor is working");
  }
  else
  {
    Serial.println("0x5A Port 0 - touch sensor is not connected correctly");
  }

  if (cap2.begin(0x5B))
  {
    Serial.println("0x5B Port 0 - touch sensor is working");
  }
  else
  {
    Serial.println("0x5B Port 0 - touch sensor is not connected correctly");
  }
  
  if (cap3.begin(0x5C))
  {
    Serial.println("0x5C Port 0 - touch sensor is working");
  }
  else
  {
    Serial.println("0x5C Port 0 - touch sensor is not connected correctly");
  }

  // Set up the second three sensors on port 0 of multiplexer
  choose_multiplexer_port(1);
  if (cap4.begin(0x5A))
  {
    Serial.println("0x5A Port 1 - touch sensor is working");
  }
  else
  {
    Serial.println("0x5A Port 1 - touch sensor is not connected correctly");
  }

  if (cap5.begin(0x5B))
  {
    Serial.println("0x5B Port 1 - touch sensor is working");
  }
  else
  {
    Serial.println("0x5B Port 1 - touch sensor is not connected correctly");
  }
  
  if (cap6.begin(0x5C))
  {
    Serial.println("0x5C Port 1 - touch sensor is working");
  }
  else
  {
    Serial.println("0x5C Port 1 - touch sensor is not connected correctly");
  }

  // Adjust the sensitivity
  choose_multiplexer_port(0);
  cap.setThresholds(touch_threshold, release_threshold);
  cap2.setThresholds(touch_threshold, release_threshold);
  cap3.setThresholds(touch_threshold, release_threshold);
  choose_multiplexer_port(1);
  cap4.setThresholds(touch_threshold, release_threshold);
  cap5.setThresholds(touch_threshold, release_threshold);
  cap6.setThresholds(touch_threshold, release_threshold);

  // Adjust sensitivity
  choose_multiplexer_port(0);
  cap.writeRegister(0x5C,0x3F);
  cap2.writeRegister(0x5C,0x3F);
  cap3.writeRegister(0x5C,0x3F);
  choose_multiplexer_port(1);
  cap4.writeRegister(0x5C,0x3F);
  cap5.writeRegister(0x5C,0x3F);
  cap6.writeRegister(0x5C,0x3F);
  
}

void loop()
{

  // Get the currently touched pins
  choose_multiplexer_port(0);
  current_pin_touched = cap.touched();
  current_pin_touched2 = cap2.touched();
  current_pin_touched3 = cap3.touched();
  choose_multiplexer_port(1);
  current_pin_touched4 = cap4.touched();
  current_pin_touched5 = cap5.touched();
  current_pin_touched6 = cap6.touched();

  // reset the sensors:
  if (Serial.available() > 0)
  {
      // read serial data:
      int serial_data = Serial.read();
      if (serial_data == 48)
      {
       //Serial.println(serial_data);
       choose_multiplexer_port(0);
       cap.begin(0x5A);
       cap2.begin(0x5B);
       cap3.begin(0x5C);
       choose_multiplexer_port(1);
       cap4.begin(0x5A);
       cap5.begin(0x5B);
       cap6.begin(0x5C);
      }
  }

  for (uint8_t i=0; i<12; i++)
  {
    choose_multiplexer_port(0);
    // Is touched in current iteration of loop but was not touched in previous iteration
    if ((current_pin_touched & _BV(i)) && !(last_pin_touched & _BV(i)) )
    {
      if (i < 10)
      {
        Serial.print(0); Serial.print(i); Serial.print(" "); Serial.println(true);
      }
      else
      {
        Serial.print(i); Serial.print(" "); Serial.println(true);
      }
    }
    
    // Is not touched in current iteration of loop but was touched in previous iteration
    if (!(current_pin_touched & _BV(i)) && (last_pin_touched & _BV(i)) )
    {
      if (i < 10)
      {
        Serial.print(0); Serial.print(i); Serial.print(" "); Serial.println(false);
      }
      else
      {
        Serial.print(i); Serial.print(" "); Serial.println(false);
      }
    }
    
    if ((current_pin_touched2 & _BV(i)) && !(last_pin_touched2 & _BV(i)) )
    {
       Serial.print(i+12); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched2 & _BV(i)) && (last_pin_touched2 & _BV(i)) )
    {
      Serial.print(i+12); Serial.print(" "); Serial.println(false);
    }

    if ((current_pin_touched3 & _BV(i)) && !(last_pin_touched3 & _BV(i)) )
    {
       Serial.print(i+24); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched3 & _BV(i)) && (last_pin_touched3 & _BV(i)) )
    {
      Serial.print(i+24); Serial.print(" "); Serial.println(false);
    }

    choose_multiplexer_port(1);
    if ((current_pin_touched4 & _BV(i)) && !(last_pin_touched4 & _BV(i)) )
    {
      Serial.print(i+36); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched4 & _BV(i)) && (last_pin_touched4 & _BV(i)) )
    {
      Serial.print(i+36); Serial.print(" "); Serial.println(false);
    }
    
    if ((current_pin_touched5 & _BV(i)) && !(last_pin_touched5 & _BV(i)) )
    {
       Serial.print(i+48); Serial.print(" "); Serial.println(true);
    }
    
    if (!(current_pin_touched5 & _BV(i)) && (last_pin_touched5 & _BV(i)) )
    {
      Serial.print(i+48); Serial.print(" "); Serial.println(false);
    }

    // we only need to check for one touch node to get to 61 keys
    if (i == 0 && (current_pin_touched6 & _BV(i)) && !(last_pin_touched6 & _BV(i)) )
    {
       Serial.print(i+60); Serial.print(" "); Serial.println(true);
    }
    
    if (i == 0 && !(current_pin_touched6 & _BV(i)) && (last_pin_touched6 & _BV(i)) )
    {
      Serial.print(i+60); Serial.print(" "); Serial.println(false);
    }
  }

  choose_multiplexer_port(0);
  last_pin_touched = current_pin_touched;
  last_pin_touched2 = current_pin_touched2;
  last_pin_touched3 = current_pin_touched3;
  choose_multiplexer_port(1);
  last_pin_touched4 = current_pin_touched4;
  last_pin_touched5 = current_pin_touched5;
  last_pin_touched6 = current_pin_touched6;
}
