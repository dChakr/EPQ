
// Servo motor test code 

#include <Servo.h>

Servo penServo;
int servoPin = 32;
//unsigned int tPeriod = 6000;

void setup() {
  penServo.attach(servoPin);
  Serial.begin(9600);
}

void loop() {
  penServo.write(45);
  Serial.print("Here");
  delay(15);
  penServo.write(0);
  delay(1000);
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
                       
