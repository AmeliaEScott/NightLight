#include "Animation.h"

#ifndef RAINBOW_H
#define RAINBOW_H

/**
 * Makes a rainbow that rotates around.
 * Clicking the button toggles this rotation.
 * Turning the dial changes the speed of rotation.
 */
class Rainbow : public Animation {
public:
    Rainbow(int rows, int cols, Neopixel* strip) : Animation(rows, cols, strip){}
    void animate(float t, float dt);
    void buttonPress(uint8_t count);
    void dialRotate(uint8_t buttonClicks, int8_t dialClicks);
private:
    float rotationSpeed = 60.0f;
    float offset = 0.0f;
    bool stopped = false;
};

#endif
