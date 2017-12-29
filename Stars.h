#include "Animation.h"

#ifndef STARS_H
#define STARS_H

#define MAX_STARS 50
#define MIN_DURATION 2.0f
#define MAX_DURATION 10.0f

/**
 * Makes a series of randomly generated twinkling stars.
 * Turning the dial adjusts the number of stars.
 * Turning the dial after one press adjusts the hue, and two clicks
 * adjusts the saturation.
 */
class Stars : public Animation {
public:
    Stars(int rows, int cols, Neopixel* strip);
    void animate(float t, float dt);
    void buttonPress(uint8_t count);
    void dialRotate(uint8_t buttonClicks, int8_t dialClicks);
private:
    int numStars = 10;
    typedef struct Star {
        uint8_t row;
        uint8_t col;
        float age;
        float maxAge;
    } Star;
    Star stars[MAX_STARS];

    float hue = 0.0f;
    float saturation = 0.0f;
};

#endif
