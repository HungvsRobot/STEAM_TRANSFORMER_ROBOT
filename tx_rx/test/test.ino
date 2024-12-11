#include "start.h"

void setup() {
  start(); 

}

void loop() {
  if(tx.available()){
    Serial.println(tx.readStringUntil('\n') + " CHECK OK ");
  }
  tx.println(" X: " + String(analogRead(A7)) +  "; Y: " + String(analogRead(A6)) + "; SW: " + String(digitalRead(A5)));
  if(Serial.available()){
    tx.println(Serial.readStringUntil('\n') + " CHECK OK ");
    Serial.println(" DONE SEND");
  }
}
 
// Địa chỉ là :     23,10,A0263A 