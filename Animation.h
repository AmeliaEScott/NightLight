#include "Neopixel.h"

#ifndef ANIMATION_H
#define ANIMATION_H

class Animation {
public:
    Animation(int rows, int columns, Neopixel* strip);
    virtual void animate(float t, float dt) = 0;
    void buttonPress();
    void buttonLongPress();
    void dialRotate(int buttonClicks, int dialClicks);
protected:
    int rows;
    int columns;
    Neopixel* strip;
};

#endif
