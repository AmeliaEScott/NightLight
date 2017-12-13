#include "Animation.h"

#ifndef RAINBOW_H
#define RAINBOW_H

class Rainbow : Animation {
public:
    Rainbow(int rows, int cols, Neopixel* strip) : Animation(rows, cols, strip){}
    void animate(float t, float dt);
};

#endif
