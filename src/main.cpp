#include <Arduino.h>
#include <FlexCAN_T4.h>

#define PICO_SERIAL   Serial7

FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> can3;

float Shoulder1  = 0;
float Shoulder2  = 0;
float Upperarm  = 0;
float Elbow  = 0;
float Forearm  = 0;
float wrist1 = 0;
float wrist2 = 0;

float finger[13]{};

IntervalTimer myTimer;
void Timtask(){

  Shoulder1 = analogRead(12)/4.f;
Shoulder2 = analogRead(13)/4.f;
Upperarm = analogRead(11)/4.f;
Elbow = analogRead(10)/4.f;
Forearm = analogRead(A16)/4.f;
wrist1 = analogRead(A14)/4.f;
wrist2 = analogRead(A15)/4.f;
finger[0] = analogRead(7)/4;
finger[1] = analogRead(5)/4;
finger[2] = analogRead(3)/4;
finger[3] = analogRead(1)/4;
finger[4] = analogRead(A17)/4;

CAN_message_t msg1;
    // msg1.flags.extended = 0;
    msg1.id = 0x111;
    // msg1.len = 5;
    // for (int i = 0; i < 5; i++) {
    //     msg1.buf[i] = data[i];
    // }
    
    msg1.buf[0] = Shoulder1;
    msg1.buf[1] = Shoulder2;
    msg1.buf[2] = Upperarm;
    msg1.buf[3] = Elbow;
    msg1.buf[4] = Forearm;
    msg1.buf[5] = wrist1;
    msg1.buf[6] = wrist2;
    msg1.buf[7] = 0;
    msg1.buf[8] = 0;

    can3.write(msg1);

    delay(2);

    CAN_message_t msg2;
    // msg2.flags.extended = 0;
    msg2.id = 0x222;
    // msg2.len = 5;
    for (int i = 0; i < 5; i++) {
        msg2.buf[i] = finger[i];
    }
    msg2.buf[6] = 0;
    msg2.buf[7] = 0;
    msg2.buf[8] = 0;
    can3.write(msg2);

  Shoulder1 = -(Shoulder1-70)/53.15775;
  if(Shoulder1>1.56){
    Shoulder1=1.56;
  }else if(Shoulder1<-3.14){
    Shoulder1 = -3.14;
  }

  Shoulder2 = -(Shoulder2-159)/53.15775;
  if(Shoulder2>3.14){
    Shoulder2=3.14;
  }else if(Shoulder2<-0.3){
    Shoulder2 = -0.3;
  }

  Upperarm = (Upperarm-75)/53.15775;
  if(Upperarm>2.29){
    Upperarm=2.29;
  }else if(Upperarm<-1.53){
    Upperarm = -1.53;
  }

  Elbow = (Elbow-255)/44.55;
  if(Elbow>0){
    Elbow=0;
  }else if(Elbow<-2.2){
    Elbow = -2.2;
  }

  Forearm = (Forearm -68)/62.39;
  if(Forearm>1.57){
    Forearm=1.57;
  }else if(Forearm<-1.57){
    Forearm = -1.57;
  }

  PICO_SERIAL.print("SS\t");
  PICO_SERIAL.print(Shoulder1,4);
  PICO_SERIAL.print("\t");
  PICO_SERIAL.print(Shoulder2,4);
  PICO_SERIAL.print("\t");
  PICO_SERIAL.print(Upperarm,4);
  PICO_SERIAL.print("\t");
  PICO_SERIAL.print(Elbow,4);
  PICO_SERIAL.print("\t");
  PICO_SERIAL.print(Forearm,4);
  PICO_SERIAL.print("\t");
  PICO_SERIAL.print(wrist1,4);
  PICO_SERIAL.print("\t");
  PICO_SERIAL.print(wrist2,4);
  PICO_SERIAL.print("\t");
  
  for (int i=0;i<13; i++){
    PICO_SERIAL.print(finger[i],4);
    PICO_SERIAL.print("\t");
  }
  PICO_SERIAL.println("EE");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);delay(400);
  PICO_SERIAL.begin(115200);
  can3.begin();
  can3.setBaudRate(1000000);
  myTimer.begin(Timtask, 10000);//μs


}

void loop() {
}