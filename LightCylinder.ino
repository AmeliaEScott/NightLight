#include <Adafruit_NeoPixel.h>
#include "Neopixel.h"
#include "Animation.h"
#include "Rainbow.h"

#define LED_PIN 6
#define COLUMNS 18
#define ROWS 7

#define ENCODER_PIN_1 10
#define ENCODER_PIN_2 11
#define BUTTON_PIN 13

Neopixel strip = Neopixel(ROWS, COLUMNS, LED_PIN, NEO_GRB + NEO_KHZ800);

unsigned int lastTime;
unsigned int currentTime;
float deltaTime;

Rainbow testAnimation = Rainbow(ROWS, COLUMNS, &strip);

void setup() {
    pinMode(ENCODER_PIN_1, INPUT_PULLUP);
    pinMode(ENCODER_PIN_2, INPUT_PULLUP);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    strip.begin();
    strip.show();
}

void loop() {
    currentTime = millis();
    deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;
    testAnimation.animate(currentTime / 1000.0f, deltaTime);

    strip.show();
}
