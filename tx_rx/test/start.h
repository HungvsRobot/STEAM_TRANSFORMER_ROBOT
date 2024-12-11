#include "Arduino.h"
#include <SoftwareSerial.h>
SoftwareSerial tx(10, 11); // RX, TX

#define a 12


void start(){
  Serial.begin(115200);
  tx.begin(9600);
  Serial.println(" OK "); 
  
  // pin set up 
  pinMode(A5, INPUT_PULLUP); 
}


