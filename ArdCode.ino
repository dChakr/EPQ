//Arduino Code v.2 - 14/09/19

#include <Servo.h>

#define xPin1 9
#define xPin2 10
#define yPin1 7
#define yPin2 8

Servo penServo;
int servoPin = 30;
unsigned int tPeriod = 600; //change when pointillism process is sorted

int speedSig = 200; //as a result of PID.Compute() from tests
unsigned int cmTime = 460;


int i = 0;
int j = 0;
int r = 20;
int c = 20;
int repos = 0;

int picCode[20][20] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,8,8,7,6,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,7,7,7,7,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,8,1,6,5,6,6,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,2,2,6,8,8,8,8,4,6,3,1,1,1,1,1},
                      {1,1,1,1,4,7,8,8,8,9,9,9,9,8,8,7,1,1,1,1},
                      {1,1,1,1,7,6,7,7,8,8,9,8,9,9,8,8,1,1,1,1},
                      {1,1,1,4,7,6,4,5,7,8,9,8,8,9,9,9,6,1,1,1},
                      {1,1,1,6,8,5,1,2,7,9,9,8,9,9,9,8,7,1,1,1},
                      {1,1,1,6,8,6,7,5,8,9,8,8,8,8,8,8,8,1,1,1},
                      {1,1,1,6,7,6,6,6,7,8,8,8,8,8,8,8,8,1,1,1},
                      {1,1,1,5,7,7,7,7,8,8,8,8,8,8,8,8,6,1,1,1},
                      {1,1,1,1,7,8,7,8,8,8,9,8,8,8,8,8,1,1,1,1},
                      {1,1,1,1,7,7,8,8,8,8,8,9,9,9,9,8,1,1,1,1},
                      {1,1,1,1,1,8,8,8,8,9,9,9,9,9,8,1,1,1,1,1},
                      {1,1,1,1,1,1,8,8,9,9,9,9,9,9,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,8,8,9,10,10,9,2,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                      {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };


void setup() {
  pinMode(xPin1, OUTPUT);
  pinMode(xPin2, OUTPUT);
  pinMode(yPin1, OUTPUT);
  pinMode(yPin2, OUTPUT);

  penServo.attach(servoPin);

  repos = cmTime*14;
  //Serial.begin(9600); leave for debugging
}


void loop() {
  for (int i = 0; i < r; i++){
    j = 0;
    for (int j = 0; j < c; j++){
      analogWrite(yPin1, speedSig);
      analogWrite(yPin2, 0);//move y-axis in cm increments
      delay(cmTime);
      analogWrite(yPin1, 0);
      Pointillism();
      delay(1000);
    }
    analogWrite(yPin2, 240); //reposition y-axis
    analogWrite(yPin1, 0);
    delay(repos);
    analogWrite(yPin2, 0);

    analogWrite(xPin1, speedSig); //move x-axis in cm increments
    analogWrite(xPin2, 0);
    delay(cmTime);
    analogWrite(xPin1, 0);
  }

}

void Pointillism() {
    unsigned long tStart = millis();
    while((millis()-tStart) < tPeriod){
      penServo.write(90);
      delay(300);
      penServo.write(45);
      delay(300);
  }
}
