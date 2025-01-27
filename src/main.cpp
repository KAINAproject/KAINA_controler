#include <Arduino.h>

int Shoulder1  = 0;
int Shoulder2  = 0;
int Upperarm  = 0;
int Elbow  = 0;
int Forearm  = 0;

int finger[5]{};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);delay(400);


}

void loop() {
Shoulder1 = analogRead(12);
Shoulder2 = analogRead(13);
Upperarm = analogRead(11);
Elbow = analogRead(10);
Forearm = analogRead(15);

finger[0] = analogRead(7);
finger[1] = analogRead(5);
finger[2] = analogRead(3);
finger[3] = analogRead(1);
finger[4] = analogRead(17);


// Serial.print("Shoulder1: ");
// Serial.print(Shoulder1);
// Serial.print(" Shoulder2: ");
// Serial.print(Shoulder2);
// Serial.print(" Upperarm: ");
// Serial.print(Upperarm);
// Serial.print(" Elbow: ");
// Serial.print(Elbow);
// Serial.print(" Forearm: ");
// Serial.println(Forearm);


Serial.print("finger[0]: ");
Serial.print(finger[0]);
Serial.print(" finger[1]: ");
Serial.print(finger[1]);
Serial.print(" finger[2]: ");
Serial.print(finger[2]);
Serial.print(" finger[3]: ");
Serial.print(finger[3]);
Serial.print(" finger[4]: ");
Serial.println(finger[4]);

delay(1);
  // put your main code here, to run repeatedly:
}
