#include <Arduino.h>
#include "buzzer.hpp"

void updateFlash(unsigned long &lastFlashTime, int timeInterval, int pin) {
  unsigned long currentTime = millis();
    if (currentTime - lastFlashTime >= (unsigned long)timeInterval) {
        lastFlashTime = currentTime;
    }

    if (currentTime - lastFlashTime < (unsigned long)(timeInterval / 2)) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}