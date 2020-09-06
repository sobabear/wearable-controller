#include<Wire.h>
#include<Mouse.h>
#include<Keyboard.h>
//아두이노 마이크로의 경우 D2 가 SDA, D3가 SCL
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup(){
  pinMode(11, INPUT_PULLUP);
  pinMode(10, OUTPUT); digitalWrite(10, LOW);

  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  Mouse.begin();
  Serial.println("Mouse Start!");
  Keyboard.begin();
}
void loop(){
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//  Serial.print("AcX = "); Serial.print(AcX);
//  Serial.print(" | AcY = "); Serial.print(AcY);
//  Serial.print(" | AcZ = "); Serial.print(AcZ);
//  
//  Serial.print(" | GyX = "); Serial.print(GyX);
//  Serial.print(" | GyY = "); Serial.print(GyY);
//  Serial.print(" | GyZ = "); Serial.println(GyZ);
  int16_t gyroX,gyroY,gyroZ;
  int sensitivity = 2500;
  gyroX = GyX / sensitivity / 1.1 ;
  gyroY = GyY / sensitivity * -1;
  gyroZ = GyZ / sensitivity * -1;
// 
//  Serial.print("gyro X = ");Serial.println(gyroX);
//  Serial.print("gyro Y = ");Serial.println(gyroY);
//  Serial.print("gyro Z = ");Serial.println(gyroZ);

  if (digitalRead(11) ==LOW){
     Mouse.move(gyroZ,gyroX);
     Serial.println("mouse");
    
  }else{
    Serial.println("keyboard");
    if(gyroY >=3){
      Keyboard.press( KEY_LEFT_ARROW);
      

    }else if (gyroY <= -3){
      Keyboard.press(KEY_RIGHT_ARROW);
    }else {
      Keyboard.release(KEY_LEFT_ARROW);
      Keyboard.release(KEY_RIGHT_ARROW);
      
    }
//      if(gyroX >=15){
//      Keyboard.press( KEY_UP_ARROW);
//    }else if (gyroX <= -14){
//      Keyboard.press(KEY_DOWN_ARROW);
//    }else {
//      Keyboard.release(KEY_UP_ARROW);
//      Keyboard.release(KEY_DOWN_ARROW);
//    }
  }
  
  
}
