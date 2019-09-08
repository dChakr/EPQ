
int r = 20;
int c = 20;

int speedSig = 105; //as a result of PID.Compute() from tests
int cmTime = 1830;

#define xPin1 9;
#define xPin2 10;
#define yPin1 7;
#define yPin2 8;

int i = 0;
int j = 0;


int picCode[r][c] = { {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
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

  Serial.begin(9600);
}

void loop() {
  for (i = 0; i < r; i++){
    for (j = 0; j < c; j++){
      analogWrite(yPin1, speedSig); //move y-axis in cm increments
      analogWrite(yPin2, 0);
      delay(cmTime);
      analogWrite(yPin1, 0);
      //enter servo stuff here
      }
    analogWrite(yPin2, speedSig); //reposition y-axis back to start
    analogWrite(yPin1, 0);
    delay(c*cmTime);
    analogWrite(yPin2,0);

    analogWrite(xPin1, speedSig); //move x-axis in cm increments
    analogWrite(xPin2, 0);
    delay(cmTime);
    analogWrite(xPin1, 0);
    }
}
