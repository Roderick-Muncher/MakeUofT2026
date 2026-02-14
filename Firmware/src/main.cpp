#include <Arduino.h>

void setup() {
  // Set the serial monitor baudrate to 9600
  Serial.begin(9600);
  
  // Output LED Level 1
  pinMode(13,OUTPUT);
  digitalWrite(13, LOW);
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

  delay(50);

  
}