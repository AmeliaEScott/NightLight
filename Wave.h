#include "Animation.h"

#ifndef WAVE_H
#define WAVE_H

class Wave : public Animation {
public:
    Wave(int rows, int cols, Neopixel* strip);
    void animate(float t, float dt);
    void buttonPress(uint8_t count);
    void dialRotate(uint8_t buttonClicks, int8_t dialClicks);
private:
    float hue;
};

#endif
