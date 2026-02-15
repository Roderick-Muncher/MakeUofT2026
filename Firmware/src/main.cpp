#include <Arduino.h>
#include "buzzer.hpp"
#include "lights.hpp"
#define D4 294
#define F4 349
#define G4 392

int playmelody2 = 0;
int previousState = 1;
const int switchPin = 2;

int previouslevel = 0;

int mymelody[] = {D4, D4, D4, 0, D4, D4, D4, 0, D4, D4, D4, 0, 0, 0,0,0, D4, 0, D4, 0, F4, 0, D4, G4,0, 0, 0, 0, 0, 0, G4, F4, D4, D4, D4, 0, D4, D4, D4, 0, D4, D4, D4, 0, 0, 0, D4, 0, D4, 0, D4, 0, F4, 0, D4, G4, 0, 0, 0, 0, 0, 0, 0, 0};

int mymelody2[] = {1661,1661,1661,1661, 0, 1245,1245,1245,1245,0, 831, 831, 831, 831, 0, 932,932,932,932,0};
int mynoteDuration2 = 50;
int mysize = sizeof(mymelody) / sizeof(mymelody[0]);
int mysize2 = sizeof(mymelody2) / sizeof(mymelody2[0]);
int mynoteDuration = 125;
int mycurrentNote = 0;
unsigned long mylastNoteTime = 0;
unsigned long myLastFlashTime = 0;
unsigned long myLastFlashTimered = 0;

void setup() {
  Serial.begin(9600);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(mybuzzerPin, OUTPUT);

  pinMode(switchPin, INPUT_PULLUP);
}

void loop() {
  int level = analogRead(0);
  int switchState = digitalRead(switchPin);

  if (previousState == 1 && switchState == 0) {
      playmelody2 = 1;
      mycurrentNote = 0;
  }

  if (playmelody2 == 1) {
      updateBuzzer(mymelody2, mysize2, mylastNoteTime, mynoteDuration2, mybuzzerPin, mycurrentNote);
      
      if (mycurrentNote >= mysize2 - 1) { 
          playmelody2 = 0;
          noTone(mybuzzerPin);
          mycurrentNote = 0;   
      }
  }

  previousState = switchState;

  if (switchState == 1) {
    Serial.println(level);

    updateFlash(myLastFlashTime, greentimeinterval, green);
    updateBuzzer(mymelody, mysize, mylastNoteTime, mynoteDuration, mybuzzerPin, mycurrentNote);

    if (level > 30) {
      digitalWrite(blue, HIGH);
    } 
    else {
      digitalWrite(blue, LOW);
    }

    if (((level + previouslevel) / 2) > 74){
      digitalWrite(red, HIGH);
    }
    else{
      digitalWrite(red, LOW);
    }
  } 
  
  else {
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }
  
  previouslevel = level;

  delay(10);
}