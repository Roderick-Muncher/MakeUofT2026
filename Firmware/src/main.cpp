#include <Arduino.h>
#include "buzzer.hpp"
#include "lights.hpp"
#define D4 294
#define F4 349
#define G4 392

int playmelody2 = 0;
int previousState = 1;
const int switchPin = 2;

int mymelody[] = {D4, D4, 0, 0, D4, D4, 0, 0, D4, D4, 0, 0, 0, 0, D4, 0, D4, 0, D4, 0, F4, 0, D4, 0, G4, G4, 0, 0, 0, D4, D4, 0, 0, D4, D4, 0, 0, D4, D4, 0, 0, 0, 0, D4, 0, D4, 0, D4, 0, F4, 0, G4, 0, D4, D4, 0, 0, 0};

int mymelody2[] = {0, 1760, 0, 1319, 0, 880, 0, 988, 0, 1500, 0};

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

  if (previousState == 1 && switchState == 0) {
      Serial.println("State Switched");
      playmelody2 = 1;  // Set the flag
      mycurrentNote = 0; // Reset note to start from the beginning
  }
  previousState = switchState;

  // 2. EXECUTION (Remove the '&& switchState == 0' condition)
  if (playmelody2 == 1) {
      updateBuzzer(mymelody2, mysize2, mylastNoteTime, mynoteDuration, mybuzzerPin, mycurrentNote);
      
      // Check if the melody is finished
      Serial.println(mysize2);
      if (mycurrentNote >= mysize2 - 1) { 
          playmelody2 = 0;      // Turn OFF the flag
          noTone(mybuzzerPin);  // Silence the buzzer
          mycurrentNote = 0;    // Reset for melody 1
          Serial.println("Melody 2 Finished");
      }
  }

  previousState = switchState;

  if (switchState == 1) {

    Serial.print("Analog value: ");
    Serial.println(level);

    updateFlash(myLastFlashTime, greentimeinterval, green);
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
    digitalWrite(green, LOW);



  }
  
  delay(10);
}