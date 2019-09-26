//Arduino Code v.2 - 26/09/19

#include <Servo.h>
#include <SD.h>
#include <SPI.h>

#define xPin1 9
#define xPin2 10
#define yPin1 7
#define yPin2 8
#define CS_PIN 53

Servo penServo;
File SD_File;
File Size_file;

int servoPin = 35;
unsigned int tPeriod = 600; //change when pointillism process is sorted

int speedSig = 200; //as a result of PID.Compute() from tests
unsigned int cmTime = 500;
int rowNum = 0;
int colNum = 0;
int repos = 0;

void setup() {
  SD.begin(CS_PIN);

  //Variables for reading in size.txt file
  int size[2];
  String element = "";
  int a = 0; //indexing variable

  //size.txt file handling to find rowNum and colNum
  Size_file = SD.open("size.txt");
  while(Size_file.available() && a<2){
  element = Size_file.readStringUntil('\r');
  size[a] = element.toInt();
  a++;
  }
  rowNum = size[0];
  colNum = size[1];
  
  //Setting up pins for motors
  pinMode(xPin1, OUTPUT);
  pinMode(xPin2, OUTPUT);
  pinMode(yPin1, OUTPUT);
  pinMode(yPin2, OUTPUT);

  penServo.attach(servoPin);

  repos = cmTime*14;
  
  //Serial.begin(9600); //leave for debugging
}

void loop() {
  int i = 0;
  int j = 0;
  int dotVal = 0;
  int cTime = 0;

//Variables for reading picCode.txt file
  int r = 0;
  int c = 0;
  int dotDen[rowNum][colNum];
  size_t n;
  char str[20];
  char *ptr; //constant pointer to non-constant character
  
  //picCode file handling
  SD_File = SD.open("picCode.TXT");

  for (r = 0; r < rowNum; r++) {
    for (c = 0; c < colNum; c++) {
      n = readField(&SD_File, str, sizeof(str), ",\n");
      dotDen[r][c] = strtol(str, &ptr, 10);}    
  }
  
  SD_File.close();

 //actual movement of machine
  for (int i = 0; i < rowNum; i++){
    j = 0;
    for (int j = 0; j < colNum; j++){
      analogWrite(yPin1, speedSig);
      analogWrite(yPin2, 0);//move y-axis in cm increments
      delay(cmTime);
      analogWrite(yPin1, 0);

      dotVal = dotDen[i][j];
      cTime = Pointillism(dotVal);

      if (dotVal != 1){
        for (int track = 0; track<(dotVal-1); track++){
        penServo.write(90);
        delay(cTime);
        penServo.write(45);
        delay(500);
        }
      }
      
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

  delay(100000000000);
}

size_t readField(File* SD_File, char* str, size_t size, char* delim) {
  char ch;
  size_t n = 0;
  while ((n + 1) < size && SD_File->read(&ch, 1) == 1) {
    // Delete CR.
    if (ch == '\r') {
      continue;
    }
    str[n++] = ch;
    if (strchr(delim, ch)) {
        break;
    }
  }
  str[n] = '\0';
  return n;
}

int Pointillism(int dotVal) {
  int track = 0;
  int cTime = 0;
  
  switch (dotVal){
    case 2://nothing happens if dotVal = 1, so neglected
      cTime = 500;
      break;
    case 3:
      cTime = 1000;
      break;
    case 4:
      cTime = 1500;
      break;
    case 5:
      cTime = 2000;
      break;
    case 6:
      cTime = 2500;
      break;
    case 7:
      cTime = 3000;
      break;
    case 8:
      cTime = 3500;
      break;
    case 9:
      cTime = 4000;
      break;
    case 10:
      cTime = 4500;
      break;    
  }

  return cTime;
}
