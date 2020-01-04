#include "Animation.h"

#ifndef CLOCK_H
#define CLOCK_H

/**
 * Just makes all of the lights one solid color.
 * Turning the dial adjusts the hue, and after one click, the saturation.
 */
class Clock : public Animation {
public:
    Clock(int rows, int cols, Neopixel* strip);
    void animate(long t, float dt);
};

#endif
