#include <SD.h>
#include <SPI.h>

int CS_PIN = 53;
#define ROW_DIM 20
#define COL_DIM 20

File picCode_File;

/*
 * Read a file one field at a time.
 *
 * file - File to read.
 *
 * str - Character array for the field.
 *
 * size - Size of str array.
 *
 * delim - String containing field delimiters.
 *
 * return - length of field including terminating delimiter.
 *
 * Note, the last character of str will not be a delimiter if
 * a read error occurs, the field is too long, or the file
 * does not end with a delimiter.  Consider this an error
 * if not at end-of-file.
 *
 */
size_t readField(File* picCode_File, char* str, size_t size, char* delim) {
  char ch;
  size_t n = 0;
  while ((n + 1) < size && picCode_File->read(&ch, 1) == 1) {
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
//------------------------------------------------------------------------------
#define errorHalt(msg) {Serial.println(F(msg)); while(1);}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Initialize the SD.
  if (!SD.begin(CS_PIN)) {
    errorHalt("begin failed");
  }

  picCode_File = SD.open("picCode.TXT");

  // Array for data.
  int array[ROW_DIM][COL_DIM];
  int i = 0;     // First array index.
  int j = 0;     // Second array index
  size_t n;      // Length of returned field with delimiter.
  char str[20];  // Must hold longest field with delimiter and zero byte.
  char *ptr;     // Test for valid field.

  // Read the file and store the data.
  
  for (i = 0; i < ROW_DIM; i++) {
    for (j = 0; j < COL_DIM; j++) {
      n = readField(&picCode_File, str, sizeof(str), ",\n");
      if (n == 0) {
        errorHalt("Too few lines");
      }
      array[i][j] = strtol(str, &ptr, 10);
      if (ptr == str) {
        errorHalt("bad number");
      }      
      if (j < (COL_DIM-1) && str[n-1] != ',') {
        errorHalt("line with too few fields");
      }
    }
    // Allow missing endl at eof.
    if (str[n-1] != '\n' && picCode_File.available()) {
      errorHalt("missing endl");
    }    
  }

  picCode_File.close();
}
//------------------------------------------------------------------------------
void loop() {
}
