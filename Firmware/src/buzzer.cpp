<<<<<<< HEAD
#include <Arduino.h>
#include "buzzer.hpp"

int melody[] = {262, 294, 330, 349, 392}; // C4, D4, E4, F4, G4
const int buzzerPin = 8;
unsigned int noteDuration = 500;
int currentNote = 0;
unsigned long lastNoteTime = 0;


//test


void updateBuzzer() {
  unsigned long currentTime = millis();

  if (currentTime - lastNoteTime >= noteDuration) {
    tone(buzzerPin, melody[currentNote], noteDuration);
    
    currentNote++;
    if (currentNote >= 5) currentNote = 0; // Loop back to start of array
    
    lastNoteTime = currentTime; 
  }
}
=======
#include "buzzer.hpp"
>>>>>>> adfeba7f30fc00ace0f3b209cab2d67cbcf100a5
