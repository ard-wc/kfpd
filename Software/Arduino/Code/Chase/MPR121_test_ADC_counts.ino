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

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t last_pin_touched = 0;
uint16_t current_pin_touched = 0;

void setup()
{

  while (!Serial)
  { 
    // delay keeps Nano from starting too fast
    delay(10);
  } 

  Serial.begin(9600);  

  if (cap.begin(0x5A))
  {
    Serial.println("0x5A Port 0 - touch sensor is working");
  }
  else
  {
    Serial.println("0x5A Port 0 - touch sensor is not connected correctly");
  }
}

void loop()
{
  current_pin_touched = cap.touched();

  for (uint8_t i=0; i<12; i++)
  {
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
  }

  last_pin_touched = current_pin_touched;
  
  for (uint8_t i=0; i<12; i++)
  {
    Serial.print(i); Serial.print("f "); Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  
  for (uint8_t i=0; i<12; i++)
  {
    Serial.print(i); Serial.print("b "); Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  delay(10);
}
