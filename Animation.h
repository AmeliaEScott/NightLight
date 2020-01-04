#include "Neopixel.h"

#ifndef ANIMATION_H
#define ANIMATION_H

/**
 * This is the base class for all animations. To implement a new animation, extend this class and implement
 * the virtual methods. Then, create an instance of it in the global animation list in LightCylinder.ino
 */
class Animation {
public:
    Animation(int rows, int columns, Neopixel* strip);
    /**
     * Called once for every "frame" of animation.
     * t is the amount of time that the arduino has been powered on, in milliseconds.
     * dt is the change in time since the previous frame, in seconds.
     */
    virtual void animate(long t, float dt) = 0;

    void updateParams(float param0, float param1, float param2);
protected:
    int rows;
    int columns;
    Neopixel* strip;

    float param0;
    float param1;
    float param2;
};

#endif
