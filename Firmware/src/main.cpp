#include <Arduino.h>
#include "buzzer.hpp"

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
  	 
  tone(buzzer, C4, 1000);  // Send 500 Hz sound signal
  delay(1000);
  noTone(9);
  tone(buzzer, D4, 1000);  // Send 500 Hz sound signal
  delay(1000);
  noTone(9);
  tone(buzzer, E4, 1000);  // Send 500 Hz sound signal
  delay(1000);
  noTone(9);	 
  tone(buzzer, F4, 1000);  // Send 500 Hz sound signal
  delay(1000);
  noTone(9);  
  tone(buzzer, G4, 1000);  // Send 500 Hz sound signal
  delay(1000);
  noTone(9);

  tone(8, 440, 100);

  delay(1000);

  
}