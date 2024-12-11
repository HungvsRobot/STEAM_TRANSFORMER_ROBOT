String data_vol = "";
double pin_cap = 0; 
void battery_check(){
  data_vol = "n2.val=" + String(int(pin_cap*100)); 
  if( millis() % 1000 == 0){
    pin_cap = ((double(pin_analog)*2)/4095)*3.3; 
    Serial2.print(data_vol);
    Serial2.write(0xff);   Serial2.write(0xff);   Serial2.write(0xff);   
    Serial.println(data_vol);
  }
}



