/* 
 * Code for Tur60 6ix cart 
 * Prelimary code
 * 
 */

int RMPin1 = 11;
int RMPin2 = 10;
int LMPin1 = 9;
int LMPin2 = 3;

int power;
int motorPower = 15; 




void setup() {
  Serial.begin(9600);

  pinMode(RMPin1, OUTPUT);
  pinMode(RMPin2, OUTPUT);  
  pinMode(LMPin1, OUTPUT);
  pinMode(LMPin2, OUTPUT);

}

void loop() {
  power =  map(motorPower, -100, 100, 124, 253);
  Serial.println("Power = " + String(power));
  analogWrite(RMPin1, power);
  analogWrite(RMPin2, power);
  analogWrite(LMPin1, power);
  analogWrite(LMPin2, power);

}
