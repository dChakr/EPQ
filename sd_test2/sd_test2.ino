#include <SD.h>
#include <SPI.h>

#define CS_PIN 53
int rowNum = 0;
int colNum = 0;
int size[2];

String element = "";

File Size_file;


void setup() {
  Serial.begin(9600);
  SD.begin(CS_PIN);
  int i = 0;
  
  Serial.println("here");
  // put your setup code here, to run once:
  Size_file = SD.open("size.txt");
/*  if (Size_file){
    Serial.print("Opened");
  }
  else{
    Serial.print("Nope");
  }*/
  while(Size_file.available() && i<2){
   element = Size_file.readStringUntil('\r');
   size[i] = element.toInt();
   i++;
   //Serial.println(index); 
  }
  rowNum = size[0];
  colNum = size[1];
  Serial.println("Rows: ");
  Serial.println(rowNum);
  Serial.println("Columns: ");
  Serial.println(colNum);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
