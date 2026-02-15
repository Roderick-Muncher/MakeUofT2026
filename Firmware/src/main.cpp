#include <Arduino.h>
#include "buzzer.hpp"
#include "lights.hpp"

const int switchPin = 2;

int mymelody[] = {
294, 294, 0, 294, 294, 0, 294, 294, 0, 0, 294, 0, 294, 0, 294, 0, 349, 0, 294, 0, 392, 392, 0, 0,
294, 294, 0, 294, 294, 0, 294, 294, 0, 0, 294, 0, 294, 0, 294, 0, 349, 0, 394, 0, 294, 294, 0, 0
};

int mysize = sizeof(mymelody) / sizeof(mymelody[0]);
int mynoteDuration = 120;
int mycurrentNote = 0;
unsigned long mylastNoteTime = 0;

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

  Serial.print("Analog value: ");
  Serial.println(level);

  if (switchState == 1) {
    updateBuzzer(mymelody, mysize, mylastNoteTime, mynoteDuration, mybuzzerPin, mycurrentNote);
    if (level > 90) {
      digitalWrite(blue, HIGH);
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH); } 
    else {
      digitalWrite(blue, LOW);
      digitalWrite(red, LOW);
      digitalWrite(green, LOW);
    }
  } 
  
  else {
    noTone(mybuzzerPin);
  }

  delay(10);
}