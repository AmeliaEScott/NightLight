#include "Neopixel.h"

#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    Animation(int rows, int columns, Neopixel* strip);
    virtual void animate(float t, float dt) = 0;
    virtual void buttonPress(uint8_t count) = 0;
    virtual void dialRotate(uint8_t buttonClicks, int8_t dialClicks) = 0;
protected:
    int rows;
    int columns;
    Neopixel* strip;
};

#endif
