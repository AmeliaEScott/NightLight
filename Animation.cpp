#include "Animation.h"

Animation::Animation(int rows, int columns, Neopixel* strip){
    this->rows = rows;
    this->columns = columns;
    this->strip = strip;
}

void Animation::buttonPress(){}
void Animation::buttonLongPress(){}
void Animation::dialRotate(int buttonClicks, int dialClicks){}

