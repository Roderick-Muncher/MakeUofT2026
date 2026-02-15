#include <Arduino.h>
#include "buzzer.hpp"
#include "lights.hpp"

const int switchPin = 2;

int mymelody[] = {
294, 294, 0, 0, 294, 294, 0, 0, 294, 294, 0, 0, 0, 0, 294, 0, 294, 0, 294, 0, 349, 0, 294, 0, 392, 392, 0, 0, 0,
294, 294, 0, 0, 294, 294, 0, 0, 294, 294, 0, 0, 0, 0, 294, 0, 294, 0, 294, 0, 349, 0, 394, 0, 294, 294, 0, 0, 0
};

int mymelody2[] = {1760, 1319, 880, 988};

int mysize = sizeof(mymelody) / sizeof(mymelody[0]);
int mysize2 = sizeof(mymelody2) / sizeof(mymelody2[0]);
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

    Serial.print("Analog value: ");
    Serial.println(level);

    updateFlash(myLastFlashTime, greentimeinterval, green);
    // updateBuzzer(mymelody2, mysize2, mylastNoteTime, mynoteDuration, mybuzzerPin, mycurrentNote);


    updateBuzzer(mymelody, mysize, mylastNoteTime, mynoteDuration, mybuzzerPin, mycurrentNote);

    if (level > 90) {
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
    } 
    else {
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
    }
  } 
  
  else {
    noTone(mybuzzerPin);
    digitalWrite(green, LOW);
  }

  delay(10);
}