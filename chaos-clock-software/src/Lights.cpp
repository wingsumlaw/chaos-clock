#include "Lights.h"

// ****** LIGHTS OBJECT ******

Adafruit_NeoPixel ClockLights = Adafruit_NeoPixel(NUM_LEDS, LED_DATA_PIN, PIXEL_TYPE);


// ****** COLORS ******
// There are likely fancy math ways to do this, but I've personally found
// that in most personal projects it is just as effective (if not more)
// to just brute force rather than to be clever

uint32_t ColorWheel[12] = { 0x33A8C7, 0x52E3E1, 0x79E484, 0xA0E426, 0xC4DF16, 0xF2E202,
                            0xFEC90B, 0xFFAB00, 0xF4413E, 0xF050AE, 0xCB5CFF, 0x9336FD };

uint8_t CurrentStep = 0;
uint8_t Direction = 1;      // 1 indicates positive movement, 0 negative

long LastTickTime = 0;

// ****** TIME STEPS ******
// I'm using an ease in-out bezier function divided into 12 steps
// Sweep happens over 5 sec

uint16_t QuadEaseTimeSteps[12] = { 85, 320, 675, 1130, 331, 1655, 2790, 3355, 3875, 4330, 4685, 4920 };


// ****** PRIVATE HELPER FUNCTIONS ******

void Update_Colors(uint8_t StepIndex);
uint8_t Get_Color_Index(uint8_t PixelNum, uint8_t StepIndex);


// ****** INIT LIGHTS ******

void Init_Lights(void) {
    // Start lights and set brightness
    // Initialize into first color set
    ClockLights.begin();
    ClockLights.setBrightness(BRIGHTNESS);
    ClockLights.show();

    // Init milli counter
    LastTickTime = millis();

    // Update colors for first step
    Update_Colors(0);
}


// ****** CLOCK TICK ******

void Tick_Lights(void) {
    // Update last tick time
    LastTickTime = millis();

    // Reset current step
    CurrentStep = 0;

    // Update direction
    if(Direction) {
        Direction = 0;
    }else{
        Direction = 1;
    }
}


// ****** LIGHT CHASE EFFECT ******

void Light_Chase(void) {
    // If enough time has passed and we are not at next tick, then update lights
    long CurrentTime = millis();
    uint8_t StepIndex;

    if((CurrentTime - LastTickTime > QuadEaseTimeSteps[CurrentStep]) && CurrentStep < 12) {
        // If going positive, then use CurrentStep, else use 12-CurrentStep
        if(Direction == 1) {
            StepIndex = CurrentStep;
        }else{
            StepIndex = 11 - CurrentStep;
        }

        Update_Colors(StepIndex);

        // Increase current step
        CurrentStep++;
    }
}


// ****** COLORS HELPERS ******

void Update_Colors(uint8_t StepIndex) {
    // For each pixel in the LED strips
    for(int i = 0; i < NUM_LEDS/2; i++) {
        // Determine color to display
        uint8_t ColorIndex = Get_Color_Index(i, StepIndex);

        // Set the colors so that the same pixel is the same color on either eye
        ClockLights.setPixelColor(i, ColorWheel[ColorIndex]);
        ClockLights.setPixelColor(i+12, ColorWheel[ColorIndex]);
    }

    // Show on strips
    ClockLights.show();
}


uint8_t Get_Color_Index(uint8_t PixelNum, uint8_t StepIndex) {
    return (PixelNum + StepIndex) % 12;
}

