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
     * t is the amount of time that the arduino has been powered on, in seconds.
     * dt is the change in time since the previous frame, in seconds.
     */
    virtual void animate(float t, float dt) = 0;
    /**
     * Called when the button is pressed, and it isn't a long press.
     */
    virtual void buttonPress(uint8_t count) = 0;
    /**
     * Called when the dial is rotated while the button is pressed.
     * buttonClicks is the number of times the button was pressed before rotating.
     * dialClicks is the number of clicks the dial has been turned.
     * If the dial was turned clockwise, dialClicks is positive. If counterclockwise,
     * it is negative.
     */
    virtual void dialRotate(uint8_t buttonClicks, int8_t dialClicks) = 0;
protected:
    int rows;
    int columns;
    Neopixel* strip;
};

#endif
