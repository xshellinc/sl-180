#include <Wire.h>
#include <ArduinoJson.h>

const int PWM_Pin[3] = {3,5,6};
//int brightnessBuffer = 100;

void setup()
{
  Serial.begin(9600);
  
  // pinMode
  for(int i=0; i<3; i++){
    pinMode(PWM_Pin[i], OUTPUT);
    analogWrite(PWM_Pin[i], 0);
  }
  delay(2);
  
  // software-soft-start
  for(int i=0; i<256; i++){
    for(int j=0; j<3; j++){
      analogWrite(PWM_Pin[j], i);
    }
    delay(2);
  }

  // I2C
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  //slowBlinkMode();
}

void receiveEvent() {
  char recvData[32] = {};
  int dataSize = Wire.available();
  for (int i = 0 ; i < dataSize ; i++) {
    recvData[i] = Wire.read();
  }
  Serial.println(recvData);
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(recvData);

  if (json.containsKey("light")) {
    updateLed(json["light"]);
  }
}

void updateLed(uint8_t brightness) {
  /*
  if(brightness>100){brightness = 100;}
  int difference = brightness - brightnessBuffer;
  if(difference>0){ //変化のベクトルが正
    for(int i=1; i<difference; i++){
      analogWrite(PWM_Pin[0], map((brightnessBuffer+i), 0, 100, 0, 255));
      analogWrite(PWM_Pin[1], map((brightnessBuffer+i), 0, 100, 0, 255));
      analogWrite(PWM_Pin[2], map((brightnessBuffer+i), 0, 100, 0, 255));
      delay(60);
    }
  }else if(difference<0){ //変化のベクトルが負
    difference *= -1;
    for(int i=1; i<difference; i++){
      analogWrite(PWM_Pin[0], map((brightnessBuffer-i), 0, 100, 0, 255));
      analogWrite(PWM_Pin[1], map((brightnessBuffer-i), 0, 100, 0, 255));
      analogWrite(PWM_Pin[2], map((brightnessBuffer-i), 0, 100, 0, 255));
      delay(60);
    }
  }else{ //変化無し
  }
  brightnessBuffer = brightness;
  */
  for(int j=0; j<3; j++){
    analogWrite(PWM_Pin[j], map(brightness, 0, 100, 0, 255));
  }
  Serial.println(brightness);
  //Serial.println(difference);
  Serial.println(map(brightness, 0, 100, 0, 255));
}

void slowBlinkMode() {
  for(int i=255; i>=0; i--){
    for(int j=0; j<3; j++){
      analogWrite(PWM_Pin[j], i);
    }
    delay(20);
  }
  delay(1000);
  for(int i=0; i<256; i++){
    for(int j=0; j<3; j++){
      analogWrite(PWM_Pin[j], i);
    }
    delay(20);
  }
  delay(1000);
}

