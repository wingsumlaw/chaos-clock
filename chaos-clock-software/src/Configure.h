// Configure file for the Chaos Clock
// Written by Wing-Sum Law, March 2023

#ifndef Configure_h
#define Configure_h

// ****** PINS ******
// If you are using different pins, here is where you would alter them

#define SOLENOID_PIN    10
#define SWITCH_PIN      2


// ****** LEDs ******
// Update LED pin here
// You can also update the type/amount of neopixels
// NOTE: if you want more than 24 LEDs, you will have to update Lights.cpp functions and colors to match

#define LED_DATA_PIN    4

#define NUM_LEDS        24
#define PIXEL_TYPE      NEO_GRB + NEO_KHZ800
#define BRIGHTNESS      20     // max = 255, but these lights are SO BRIGHT


// ****** MISC VALUES ******

#define SECOND          1000000

#endif

