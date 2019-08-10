/*
 * wow we actually got here
 * 
 * all programs combined (just the throttle and the LED)
 * 
 * yeet
 * 
 */


// throttle stuff
const int throttlePin = A0; // input for throttle

const int rightMPin = 9; // pin for first motor PWM
const int leftMPin = 10; // pin for second motor PWM

int throttle;
int power;


// light stuff
const int lightPin = 3;

#include <Adafruit_NeoPixel.h>

const int numLeds = 30;
const int delayTime = 20;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(numLeds, lightPin, NEO_GRB + NEO_KHZ800);



// now for the actual stuff
void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.setBrightness(100); // 1/3 brightness

  strip.show(); // Initialize all pixels to 'off'

  pinMode(throttlePin, INPUT);

  pinMode(rightMPin, OUTPUT);
  pinMode(leftMPin, OUTPUT);

  pinMode(lightPin, OUTPUT);
  
}

void loop() {

  lights(); // base function for all light operations
  
  serialOutput(); // printing out some information
  
  throttle = analogRead(throttlePin);

  power = map(throttle, 167, 882,  188, 240);

  motorsMove();
}

void motorsMove() {
  analogWrite(rightMPin, power);
  analogWrite(leftMPin, power);
}

void serialOutput() { // info from throttle and motors for debugging/testing
  Serial.print("Throttle: " + String(analogRead(throttlePin)));
  Serial.println(" Motor power: " + String(power));
}

void lights() { // base for lights
  if (millis() % 10000 > 5000) {
    if (millis() % 2000 > 1000) {
      RunningLights(252, 3, 3, 100);
    
    }
    else {
      RunningLights(255, 247, 247, 100);
    }
  }
  
  else theaterChaseRainbow(20, 200);
}

void theaterChaseRainbow(int colorDelay, int speedDelay) { // rainbow pattern
  byte *c;

  int colorTime = (millis()/colorDelay)%256;
  int offTime = (millis()/speedDelay)%3;
  
  for (int i=0; i < numLeds; i=i+3) {
    c = WheelF( (i+colorTime) % 255);
    strip.setPixelColor(i+offTime, *c, *(c+1), *(c+2));    //turn every third pixel on
  }
  strip.show();
  
  for (int i=0; i < numLeds; i=i+3) {
    strip.setPixelColor(i+offTime, 0,0,0);

  }

}






byte * WheelF(byte WheelPos) { // required for rainbow pattern
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}


void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position = 0;

  int posTime = (millis() / WaveDelay) % (numLeds * 2);

  for (int i = 0; i < numLeds; i++) {
    // sine wave, 3 offset waves make a rainbow!
    //float level = sin(i+Position) * 127 + 128;
    //setPixel(i,level,0,0);
    //float level = sin(i+Position) * 127 + 128;
    strip.setPixelColor(i, ((sin(i + posTime) * 127 + 128) / 255)*red,
                        ((sin(i + posTime) * 127 + 128) / 255)*green,
                        ((sin(i + posTime) * 127 + 128) / 255)*blue);
  }

  strip.show();

}
