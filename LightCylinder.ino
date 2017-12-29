#include <Adafruit_NeoPixel.h>
#include "Neopixel.h"
#include "Animation.h"
#include "Rainbow.h"
#include "Static.h"
#include "Stars.h"

#define LED_PIN 6
#define COLUMNS 18
#define ROWS 7

#define ENCODER_PIN_1 2
#define ENCODER_PIN_2 3
#define BUTTON_PIN 12

// Maximum amount of time between double-clicks
#define CLICK_DELAY 700
// Duration of button press to make it a long-press
#define LONG_PRESS_TIME 900
// All button presses shorter than this amount of time are ignored, since I
// was too lazy to add a capacitor to the physical circuit
#define DEBOUNCE_TIME 10

// Maximum brightness of the entire device, out of 255
// (This is needed because I made some wires too thin, so they can't handle much current)
#define MAX_BRIGHTNESS 100
// Adjusts how much the brightness changes with each click of the dial
#define BRIGHTNESS_SCALING 0.15f

Neopixel strip = Neopixel(ROWS, COLUMNS, LED_PIN, NEO_GRB + NEO_KHZ800);

enum State {
    waitingForButtonPress,
    waitingForButtonRelease,
    waitingForButtonReleaseAfterLongPress,
    turningDialPressed,
    idle
};

// Last time the loop() function ran, in milliseconds
long lastTime;
// The time at the start of the current loop()
long currentTime;
// Time difference between then and now, in seconds
float deltaTime;

// Last time the button was pressed down, in milliseconds
long lastButtonDown = 0;
// Last time the button was released, in milliseconds
long lastButtonUp = 0;
// True iff the button is currently pressed (After accounting for debouncing)
bool buttonPressed = false;
// True iff the button is pressed (Before accounting for debouncing)
bool buttonSignal = false;
// Number of times the button has been pressed
uint8_t buttonPressCount = 0;

// Boy, this is a lot of global variables, huh?
// I guess this is what happens when I procrastinate and don't give myself
// enough time to do things properly.
volatile int8_t lastEncoderState = 0;
volatile int8_t currentEncoderState = 0;
volatile int8_t encoderPosition = 0;
volatile int8_t encoderClick = 0;

State state = idle;

// Overall brightness of the lights, 0-255
float brightness = 10.0f;

// Here, the animations are being set up. Is there a better way to do this? Probably
Rainbow rainbow = Rainbow(ROWS, COLUMNS, &strip);
Static staticLight = Static(ROWS, COLUMNS, &strip);
Stars stars = Stars(ROWS, COLUMNS, &strip);
#define NUM_ANIMATIONS 3
int currentAnimation = 0;
Animation* animations[NUM_ANIMATIONS] = {&rainbow, &staticLight, &stars};


void setup() {
    pinMode(ENCODER_PIN_1, INPUT_PULLUP);
    pinMode(ENCODER_PIN_2, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_1), pollEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_2), pollEncoder, CHANGE);
    
    strip.begin();
    strip.show();
}

// The two pins of the rotary encoder output numbers in gray code.
// This function just converts that to a regular ol' number.
int8_t encoderToNumber(int8_t pin1, int8_t pin2){
    int8_t result = pin2 << 1;
    result += (pin2 ^ pin1);
    result = (result + 2) % 4;
    return result;
}

void pollEncoder(){
    lastEncoderState = currentEncoderState;
    currentEncoderState = encoderToNumber(digitalRead(ENCODER_PIN_1), digitalRead(ENCODER_PIN_2));
    if(currentEncoderState != lastEncoderState){
        if(currentEncoderState == 3 && lastEncoderState == 0){
            encoderPosition += 1;
        }else if(currentEncoderState == 0 && lastEncoderState == 3){
            encoderPosition += -1;
        }else{
            encoderPosition += (lastEncoderState - currentEncoderState);
        }
    }
    if(encoderPosition % 4 == 0){
        encoderClick += encoderPosition / 4;
        encoderPosition = 0;
    }
}

void loop() {
    currentTime = millis();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    bool buttonWasPressed = buttonPressed;
    buttonSignal = digitalRead(BUTTON_PIN) == LOW;
    if(buttonSignal && !buttonWasPressed && currentTime - lastButtonUp > DEBOUNCE_TIME){
        buttonPressed = true;
        lastButtonDown = currentTime;
    }else if(!buttonSignal && buttonWasPressed && currentTime - lastButtonDown > DEBOUNCE_TIME){
        buttonPressed = false;
        lastButtonUp = currentTime;
    }
    
    if(state == idle){
        if(buttonPressed){
            state = waitingForButtonRelease;
        }else if(encoderClick != 0){
            turnDial();
        }
    }else if(state == turningDialPressed){
        if(encoderClick != 0){
            turnDial();
        }else if(!buttonPressed){
            state = idle;
            buttonPressCount = 0;
        }
    }else if(state == waitingForButtonRelease){
        if(!buttonPressed){
            state = waitingForButtonPress;
            buttonPressCount++;
        }else if(encoderClick != 0){
            state = turningDialPressed;
            turnDial();
        }else if(currentTime - lastButtonDown > LONG_PRESS_TIME){
            state = waitingForButtonReleaseAfterLongPress;
        }
    }else if(state == waitingForButtonReleaseAfterLongPress){
        if(encoderClick != 0){
            state = turningDialPressed;
            turnDial();
        }else if(!buttonPressed){
            currentAnimation = (currentAnimation + 1) % NUM_ANIMATIONS;
            state = idle;
            buttonPressCount = 0;
        }
    }else if(state == waitingForButtonPress){
        if(currentTime - lastButtonDown > CLICK_DELAY || encoderClick != 0){
            animations[currentAnimation]->buttonPress(buttonPressCount);
            buttonPressCount = 0;
            state = idle;
        }else if(buttonPressed){
            state = waitingForButtonRelease;
        }
        
        if(encoderClick != 0){
            state = idle;
            turnDial();
        }
    }

    encoderClick = 0;
    
    animations[currentAnimation]->animate(currentTime / 1000.0f, deltaTime);
    strip.setBrightness((int) brightness);
    strip.show();
}

void turnDial(){
    if(state == turningDialPressed){
        animations[currentAnimation]->dialRotate(buttonPressCount, encoderClick);
    }else{
        brightness = brightness * (1.0f + (encoderClick * BRIGHTNESS_SCALING));
        if(brightness < 1.0f && encoderClick > 0){
            brightness = 1.0f;
        }else if(brightness > MAX_BRIGHTNESS){
            brightness = MAX_BRIGHTNESS;
        }
    }
}

