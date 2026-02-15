#include <Arduino.h>
#include "buzzer.hpp"
#include "lights.hpp"

const int switchPin = 2;

int mymelody[] = {
294, 294, 0, 0, 294, 294, 0, 0, 294, 294, 0, 0, 0, 0, 294, 0, 294, 0, 294, 0, 349, 0, 294, 0, 392, 392, 0, 0, 0,
294, 294, 0, 0, 294, 294, 0, 0, 294, 294, 0, 0, 0, 0, 294, 0, 294, 0, 294, 0, 349, 0, 394, 0, 294, 294, 0, 0, 0
};

int mysize = sizeof(mymelody) / sizeof(mymelody[0]);
int mynoteDuration = 100;
int mycurrentNote = 0;
unsigned long mylastNoteTime = 0;
unsigned long myLastFlashTime = 0;

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

  if (switchState == 1) {
    Serial.println(level);

    updateFlash(myLastFlashTime, greentimeinterval, green);

    updateBuzzer(mymelody, mysize, mylastNoteTime, mynoteDuration, mybuzzerPin, mycurrentNote);

    if (level > 90) {
      digitalWrite(blue, HIGH);
    } 
    else {
      digitalWrite(blue, LOW);
    }
  } 
  
  else {
    noTone(mybuzzerPin);
    digitalWrite(green, LOW);
  }

  delay(10);
}