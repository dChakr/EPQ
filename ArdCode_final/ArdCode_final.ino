//Arduino Code v.3 - 9/10/19

#include <Servo.h>
#include <SD.h>
#include <SPI.h>

#define xPin1 9
#define xPin2 10
#define yPin1 7
#define yPin2 8
#define CS_PIN 53
#define servoPin 32

Servo penServo;
File SD_File;
File Size_file;

int speedSig_x = 100; //as a result of PID.Compute() from tests
int speedSig_y = 60;
unsigned int cmTime_x = 300;
unsigned int cmTime_y = 300;
int rowNum = 20;
int colNum = 20;
                     

void setup() {
  //open SD card for access
  if (!SD.begin(CS_PIN)){
    Serial.print("Here");
    };

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
}

void loop() {
  int i = 0;
  int j = 0;
  int dotVal = 0;
  int pos = 0;
  unsigned int cTime = 0;
  bool Stop = true;

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
 penServo.write(45);
  for (int i = 0; i < rowNum; i++){
    j = 0;
    for (int j = 0; j < colNum; j++){ //move y-axis in cm increments
      analogWrite(yPin1, speedSig_y);
      analogWrite(yPin2, 0);
      delay(cmTime_y);
      analogWrite(yPin1, 0);

      dotVal = dotDen[i][j];
      cTime = Pointillism(dotVal); //Call Pointillism function to control repetitions of servo motor
      
      if (dotVal != 1){
        for (int track = 0; track<(dotVal-1); track++){
          for (pos = 45; pos<=90; pos+=1){
            penServo.write(pos);
            delay(15);
            }
          delay(cTime);  
          for (pos = 90; pos>=45; pos-=1){
            penServo.write(pos);
            delay(15);
          }
        }
      }
      delay(1000);
    }
    
    int a = 0; //reposition y-axis back to starting position for next row
    for (int a = 0; a < colNum; a++){
      analogWrite(yPin2, speedSig_y);
      analogWrite(yPin1, 0);
      delay(cmTime_y);
      analogWrite(yPin2, 0);
      delay(100);
    }
    Serial.println(i); //move the x-axis
    analogWrite(xPin1, speedSig_x);
    analogWrite(xPin2, 0);
    delay(cmTime_x);
    analogWrite(xPin1, 0);
  }

  while (Stop == true){ //infinite loop so machine stops moving after one drawing is drawn
    Serial.print("Stop");
  }

}

//function to read information from picCode file
size_t readField(File* SD_File, char* str, size_t size, char* delim) {
  char ch;
  size_t n = 0;
  while ((n + 1) < size && SD_File->read(&ch, 1) == 1) {
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

// fucntion to allocate time for contact on paper to a element based on its value of in dotDen 

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
