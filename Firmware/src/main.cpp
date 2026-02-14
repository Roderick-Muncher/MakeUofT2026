#include "buzzer.hpp"

// Note constants (ensure these match your definitions)

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