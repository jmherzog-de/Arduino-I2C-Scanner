/*
 * Copyright (c) 2020 Jean-Marcel Herzog
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
 * associated documentation files (the "Software"), to deal in the Software without restriction, including 
 * without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the 
 * following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial 
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 
 */

#include <Wire.h>

#define BAUDRATE  9600

//
// global variables
//
uint8_t i2caddr;
bool start_scan = false;
char recv;


// hardware initialization
void setup() {

  Serial.begin(BAUDRATE);

  // wait, until user connect via serial port.
  while(!Serial);

  Wire.begin();

  Serial.println("---I2C-Scanner---");
  Serial.println("Scanvorgang durch Eingabe von 's' starten.");
}

// search for I2C slaves
void scan(unsigned long clck_hz){
  Wire.setClock(clck_hz);
  for(i2caddr = 1; i2caddr < 128; i2caddr++){
    Wire.beginTransmission(i2caddr);
    if(Wire.endTransmission() == 0){
      Serial.print("Teilnehmer mit Adresse ");
      Serial.print(i2caddr, HEX);
      Serial.println(" gefunden.");
    }
  }
}

void loop() {

  // wait for start command
  if(Serial.available() > 0){
    recv = Serial.read();
    if(recv == 's'){
      start_scan = true;
    }
  }
  
  if(start_scan){
    Serial.println("Scan starts with 100 kHz");
    scan(100000UL);
    Serial.println("Scan starts with 400 kHz");
    scan(400000UL);
    Serial.println("Scan done.");
    Serial.println("\nRescan start with input 's'.");

    start_scan = false;
  }
}
