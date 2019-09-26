//Arduino Code v.2 - 14/09/19

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

int servoPin = 30;
unsigned int tPeriod = 600; //change when pointillism process is sorted

int speedSig = 200; //as a result of PID.Compute() from tests
unsigned int cmTime = 460;


void setup() {
  int repos = 0;
  SD.begin(CS_PIN);

  //Variables for reading in size.txt file
  int size[2];
  String element = "";
  int rowNum = 0;
  int colNum = 0;
  int a = 0; //indexing variable

  //size.txt file handling to find rowNum and colNum
  Size_file = SD.open("size.txt");
  while(Size_file.available() && i<2){
  element = Size_file.readStringUntil('\r');
  size[i] = element.toInt();
  i++;
  }
  rowNum = size[0];
  colNum = size[1];
  
  //Variables for reading picCode.txt file
  int r = 0;
  int c = 0;
  int dotDen[rowNum][colNum];
  size_t n;
  char str[20];
  char *ptr; //constant pointer to non-constant character
  
  //Setting up pins for motors
  pinMode(xPin1, OUTPUT);
  pinMode(xPin2, OUTPUT);
  pinMode(yPin1, OUTPUT);
  pinMode(yPin2, OUTPUT);

  penServo.attach(servoPin);

  repos = cmTime*14;
  
  //Serial.begin(9600); //leave for debugging

  //picCode file handling:
  SD_File = SD.open("picCode.TXT");

  for (r = 0; r < rowNum; r++) {
    for (c = 0; c < colNum; c++) {
      n = readField(&SD_File, str, sizeof(str), ",\n");
      if (n == 0) {
        Serial.println("Too few lines");
      }
      dotDen[r][c] = strtol(str, &ptr, 10);
      
      /*if (ptr == str) { //leave in for debugging - remove at the end
        Serial.println("bad number");
      }      
      if (j < (COL_DIM-1) && str[n-1] != ',') { //leave in for debugging - remove at end
        Serial.println("line with too few fields");
      }
    }
    // Allow missing endl at eof.
    if (str[n-1] != '\n' && SD_File.available()) { //leave in for debugging
      Serial.println("missing endl");
    */}    
  }

 SD_File.close();
  
}


void loop() {

  int i = 0;
  int j = 0;

  for (int i = 0; i < rowNum; i++){
    j = 0;
    for (int j = 0; j < colNum; j++){
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

void Pointillism() {
    unsigned long tStart = millis();
    while((millis()-tStart) < tPeriod){
      penServo.write(90);
      delay(300);
      penServo.write(45);
      delay(300);
  }
}
