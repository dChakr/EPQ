// Servo motor test code 

#include <Servo.h>

Servo penServo;
int servoPin = 32;
//unsigned int tPeriod = 6000;
int pos =0; //added this to store servo position
void setup() {
  penServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
 /*for (pos = 45; pos <=90; pos +=1){//to move from 0 to 45 degrees
    penServo.write(pos);
    delay(15);    //now pausing for 15ms
  }
 delay(1000);
 for (pos = 90; pos >=45; pos -=1){ //to move from 45 to 0degrees
    penServo.write(pos);
    delay(15);//another 15ms pause - changing this affects speed of turn
  }*/

for (pos = 45; pos<=90; pos+=1){
   penServo.write(pos);
   delay(15);
   }
delay(3000); 
for (pos = 90; pos>=45; pos-=1){
  penServo.write(pos);
  delay(15);
}
 //delay(1000); // change this for how long the pen stays up
  /*unsigned int tStart = millis();
  while((millis()-tStart) < tPeriod){
    penServo.write(90);
    delay(300);
    penServo.write(45);
    delay(300);
  }
  delay(1000000);
*/
//}
}
                       
