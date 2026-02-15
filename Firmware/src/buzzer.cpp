#include <Arduino.h>
#include "buzzer.hpp" 

void updateBuzzer(int melody[], int arraySize, unsigned long &lastNoteTime, int noteDuration, int buzzerPin, int &currentNote) {
  unsigned long currentTime = millis();

  if (currentTime - lastNoteTime >= (unsigned long)noteDuration) {
<<<<<<< HEAD
<<<<<<< HEAD
    tone(buzzerPin, melody[currentNote], noteDuration + 50);
     
=======
=======
>>>>>>> 89b4fab7581cd7d152df4f0af34f1dddd0957975
    tone(buzzerPin, melody[currentNote], noteDuration + 20);
    
>>>>>>> 89b4fab7581cd7d152df4f0af34f1dddd0957975
    currentNote++;
    if (currentNote >= arraySize) currentNote = 0; 
    
    lastNoteTime = currentTime; 
  }
}