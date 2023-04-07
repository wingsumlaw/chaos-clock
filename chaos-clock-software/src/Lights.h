// For running the LEDs on the Chaos Clock
// Written by Wing-Sum Law, March 2023

#ifndef Lights_h
#define Lights_h

#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#include "Configure.h"

void Init_Lights(void);
void Tick_Lights(void);
void Light_Chase(void);

#endif