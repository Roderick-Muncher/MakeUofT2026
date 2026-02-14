#include <Arduino.h>
#include "buzzer.hpp"

// Note constants (ensure these match your definitions)
int melody[] = {262, 294, 330, 349, 392}; // C4, D4, E4, F4, G4
const int buzzerPin = 8;
unsigned int noteDuration = 500;
int currentNote = 0;
unsigned long lastNoteTime = 0;

void updateBuzzer() {
  unsigned long currentTime = millis();

  if (currentTime - lastNoteTime >= noteDuration) {
    tone(buzzerPin, melody[currentNote], noteDuration);
    
    currentNote++;
    if (currentNote >= 5) currentNote = 0; // Loop back to start of array
    
    lastNoteTime = currentTime; 
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // LED pin
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int level = analogRead(0);

  Serial.print("Analog value: ");
  Serial.println(level);

  if (level > 90) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);
  }

  // 4. Music plays in the background constantly
  updateBuzzer();

  // Tiny delay to keep the Serial Monitor readable
  delay(10);
}