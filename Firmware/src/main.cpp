#include <Arduino.h>

void setup() {
  // Set the serial monitor baudrate to 9600
  Serial.begin(9600);
  
  // Output LED Level 1
  pinMode(13,OUTPUT);
}

void loop() {

  int level;
  level = analogRead(0);
  
  // Print "Analog value:" in serial monitor
  Serial.println("Analog value:");
  // Print output voltage in serial monitor
  Serial.println(level);
  
  // Turn off all the led initially
  digitalWrite(13,LOW);
  
    // Splitting 1023 into 5 level => 200, 400, 600, 800, 1023
    // Based on the ADC output, LED indicates the level (1 to 5)
  
  if (level>200)
  {
    // LEVEL 1 LED
    digitalWrite(13,HIGH);
  }

  
}