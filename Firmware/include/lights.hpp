#ifndef LIGHTS_HPP
#define LIGHTS_HPP
#include <Arduino.h>

void updateFlash(unsigned long &lastFlashTime, int timeInterval, int pin);

const int blue = 13;
const int red = 12;
const int green = 11;

const int greentimeinterval = 500;
const int redtimeinterval = 100;


#endif