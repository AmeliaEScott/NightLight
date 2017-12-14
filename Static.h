#include "Animation.h"

#ifndef STATIC_H
#define STATIC_H

class Static : public Animation {
public:
    Static(int rows, int cols, Neopixel* strip);
    void animate(float t, float dt);
    void buttonPress(uint8_t count);
    void dialRotate(uint8_t buttonClicks, int8_t dialClicks);
private:
    float hue, saturation;
};

#endif
