#include <Arduino.h>
#include "buzzer.hpp"

int melody[] = {262, 294, 330, 349, 392}; // C4, D4, E4, F4, G4
unsigned int noteDuration = 500;
int currentNote = 0;
unsigned long lastNoteTime = 0;

void updateBuzzer(int melody[]) {
  unsigned long currentTime = millis();

  // Only play the song if the "Muncher" is being pressed
  if (currentTime - lastNoteTime >= noteDuration) {
    tone(8, melody[currentNote], noteDuration);
    
    currentNote++;
    if (currentNote >= (sizeof(melody) / sizeof(melody[0]))) currentNote = 0; // Reset song after G4
    
    lastNoteTime = currentTime; // Reset the timer
  }
  else {
  noTone(8);
  currentNote = 0; // Optional: Reset song to beginning if released
  }
}

void setup() {
  // Set the serial monitor baudrate to 9600
  Serial.begin(9600);
  
  // Output LED Level 1
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);

  pinMode(8,OUTPUT);
  
}

void loop() {

  int level;
  level = analogRead(0);

  Serial.println("Analog value:");
  Serial.println(level);
  
    // Splitting 1023 into 5 level => 200, 400, 600, 800, 1023
    // Based on the ADC output, LED indicates the level (1 to 5)
  
  if (level>90)
  {
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }

  updateBuzzer(melody);

  delay(1000);

  
}