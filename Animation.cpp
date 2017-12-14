#include "Animation.h"

Animation::Animation(int rows, int columns, Neopixel* strip){
    this->rows = rows;
    this->columns = columns;
    this->strip = strip;
}
