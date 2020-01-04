#include "Animation.h"

Animation::Animation(int rows, int columns, Neopixel* strip){
    this->rows = rows;
    this->columns = columns;
    this->strip = strip;
}

void Animation::updateParams(float param0, float param1, float param2){
    this->param0 = param0;
    this->param1 = param1;
    this->param2 = param2;
}
