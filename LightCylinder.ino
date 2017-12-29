#include <Adafruit_NeoPixel.h>
#include "Neopixel.h"
#include "Animation.h"
#include "Rainbow.h"
#include "Static.h"

#define LED_PIN 6
#define COLUMNS 18
#define ROWS 7

#define ENCODER_PIN_1 2
#define ENCODER_PIN_2 3
#define BUTTON_PIN 12

#define CLICK_DELAY 700
#define LONG_PRESS_TIME 900

#define MAX_BRIGHTNESS 100
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
// True iff the button is currently pressed
bool buttonPressed = false;
// Number of times the button has been pressed
uint8_t buttonPressCount = 0;

volatile int8_t lastEncoderState = 0;
volatile int8_t currentEncoderState = 0;
volatile int8_t encoderPosition = 0;
volatile int8_t encoderClick = 0;

State state = idle;

// Overall brightness of the lights, 0-255
float brightness = 10.0f;

Rainbow rainbow = Rainbow(ROWS, COLUMNS, &strip);
Static staticLight = Static(ROWS, COLUMNS, &strip);
#define NUM_ANIMATIONS 2
int currentAnimation = 0;
Animation* animations[NUM_ANIMATIONS] = {&rainbow, &staticLight};


void setup() {
    pinMode(ENCODER_PIN_1, INPUT_PULLUP);
    pinMode(ENCODER_PIN_2, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_1), pollEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_PIN_2), pollEncoder, CHANGE);
    
    strip.begin();
    strip.show();
}

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
    buttonPressed = digitalRead(BUTTON_PIN) == LOW;
    if(buttonPressed && !buttonWasPressed){
        lastButtonDown = currentTime;
        Serial.print("Button was pressed at ");
        Serial.println(lastButtonDown);
    }else if(!buttonPressed && buttonWasPressed){
        lastButtonUp = currentTime;
        Serial.print("Button was released at ");
        Serial.println(lastButtonUp);
    }
    
    if(state == idle){
        if(buttonPressed){
            state = waitingForButtonRelease;
            Serial.print("Button was pressed from idle, at ");
            Serial.println(lastButtonDown);
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

