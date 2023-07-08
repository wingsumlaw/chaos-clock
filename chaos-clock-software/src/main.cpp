// Software for Chaos Clock
// Written by Wing-Sum Law, March 2023

#include <Arduino.h>
#include "Lights.h"
#include "TimerOne.h"

// ****** STATE MACHINE SET UP ******

typedef enum {
    PAUSED,
    KEEPING_TIME
} State_t;

State_t CurrentState;

uint8_t LastSolenoidState = LOW;


// ****** FUNCTIONS ******

// For interrupts
void Tick(void);
void Switch(void);

// Other helpers
void Switch_Solenoid(void);


// ****** SETUP ******

void setup() {
    // Set up serial monitor
    Serial.begin(9600);

    // Set up pins
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    pinMode(SOLENOID_PIN, OUTPUT);

    // Configure switch interrupt on changing
    attachInterrupt(digitalPinToInterrupt(SWITCH_PIN), Switch, CHANGE);

    // Set up timer 1
    Timer1.attachInterrupt(Tick);

    // Init into correct state
    Switch();

    // Init lights
    Init_Lights();
}


// ****** MAIN LOOP ******

void loop() {
    Light_Chase();
}


// ****** OTHER HELPERS ******

void Switch_Solenoid(void) {
    // If solenoid was last LOW, then turn to HIGH
    // and vice versa
    if(LastSolenoidState == LOW) {
        digitalWrite(SOLENOID_PIN, HIGH);
        LastSolenoidState = HIGH;
    }else{
        digitalWrite(SOLENOID_PIN, LOW);
        LastSolenoidState = LOW;
    }
}


// ****** INTERRUPT FUNCTIONS ******

void Tick(void) {
    Switch_Solenoid();
    Tick_Lights();
}


void Switch(void) {
    uint8_t CurrentSwitchState = digitalRead(SWITCH_PIN);
    if(CurrentSwitchState) {
        // If reading is high, then enter into paused i.e. nothing running
        CurrentState = PAUSED;

        // Stop timer
        Timer1.stop();

        // Turn solenoid off while paused to keep it from overheating
        digitalWrite(SOLENOID_PIN, LOW);
        LastSolenoidState = LOW;

    }else{
        // If reading is low, then enter into running
        CurrentState = KEEPING_TIME;

        // Start timer to start counting
        Timer1.initialize(SECOND);

    }
}

