#include <Arduino.h>
#include "buzzer.hpp"

void updateBuzzer(int melody[], int arraySize, unsigned long &lastNoteTime, int noteDuration, int buzzerPin, int &currentNote) {
  unsigned long currentTime = millis();

  if (currentTime - lastNoteTime >= (unsigned long)noteDuration) {
    tone(buzzerPin, melody[currentNote], noteDuration + 20);
    
    currentNote++;
    if (currentNote >= arraySize) currentNote = 0; 
    
    lastNoteTime = currentTime; 
  }
}