#include <Wire.h>
#include <string.h> 
#include "BluetoothSerial.h"
#include "ESP32TimerInterrupt.h"
#include "IO_CONFIG.h"
#include "BUTTON_INDEX.h"
#include "esp_gap_bt_api.h"

ESP32Timer myTimer(0);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

uint8_t mac_address[] = {0xA9,0x9A,0x07,0x04,0x55,0x7C}; // Địa chỉ tay cầm
uint32_t tsLastReport = 0;
int  rssi_value = 0;

void setup(){
    //myTimer.attachInterruptInterval(30000, timerCallback);
    Serial.begin(115200);
    Serial2.begin(9600);
    SerialBT.begin("TAY_DIEU_KHIEN", true); 

    SerialBT.setPin("2708");

    // if (SerialBT.connect(mac_address, 0, ESP_SPP_SEC_ENCRYPT |  ESP_SPP_SEC_AUTHENTICATE, ESP_SPP_ROLE_MASTER)) {
    //       Serial.println(" Done connection ( connect successfull ) JDY-31");
    // } else {
    //     Serial.println("Fail connect!! ");
    // }
    while(!SerialBT.connect(mac_address, 0, ESP_SPP_SEC_ENCRYPT |  ESP_SPP_SEC_AUTHENTICATE, ESP_SPP_ROLE_MASTER) && !button23){
      Serial.println("CONNECTING ...... ROBOT");
      //if(button23) break;
    }
    Serial.println(" Done connection ( connect successfull ) ROBOTTTT ");

    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);

    pinMode(22, INPUT);
    pinMode(21, INPUT);
    pinMode(19, INPUT);
    pinMode(18, INPUT);
    pinMode(35, INPUT);
    pinMode(32, INPUT);
    pinMode(25, INPUT);
    pinMode(33, INPUT);
    pinMode(34, INPUT);
    pinMode(23, INPUT);
    pinMode(15, INPUT);  // Chưa kết nối
    pinMode(5, INPUT);
    pinMode(26, INPUT);
    pinMode(39, INPUT);
    pinMode(36, INPUT);

    pinMode(26, INPUT);  // PIN
}

bool tt_led_14 = 0, tt_gui = 0; 
uint32_t time_led = 0; 
uint32_t last_frame2 = 0, last_frame1 = 0; 


String data = ""; 
String data1 = "";
uint32_t timer_send = 0; 




void loop(){
 

  if(SerialBT.available()){
    data1 = SerialBT.readStringUntil('\n');
    Serial.println(data1);
    Serial2.print(data1);
    Serial2.write(0xff);   Serial2.write(0xff);   Serial2.write(0xff);
    digitalWrite(12, 1);
  }else{
    digitalWrite(12, 0);
  }

  if(Serial2.available()){
    
  }

  updateButtons(); 
  battery_check();
  if(millis() - timer_send >= 10){
    if( frame2 != last_frame2 || last_frame1 != frame1){
      for( int i = 0; i< 10; i++){
        SerialBT.write(frame[i]);
      }
      digitalWrite(14, 1);

      last_frame2 = frame2; 
      last_frame1 = frame1; 

      data = "sys2=" + String(byte_analog[1]); 
      Serial2.print(data);
      Serial2.write(0xff);   Serial2.write(0xff);   Serial2.write(0xff);   

      data = "sys1=" + String(byte_analog[3]); 
      Serial2.print(data);
      Serial2.write(0xff);   Serial2.write(0xff);   Serial2.write(0xff);   
 
    }else{
      digitalWrite(14, 0);
    }
    timer_send = millis(); 
  }  

  if(SerialBT.hasClient()){
    Serial2.print("n3.val=40");
    Serial2.write(0xff);   Serial2.write(0xff);   Serial2.write(0xff); 
  }else{
    Serial2.print("n3.val=100");
    Serial2.write(0xff);   Serial2.write(0xff);   Serial2.write(0xff); 
  }


}
