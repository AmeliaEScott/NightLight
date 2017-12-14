#include "Rainbow.h"

void Rainbow::animate(float t, float dt){
    Neopixel::FloatHSV hsv = {0.0f, 1.0f, 1.0f};
    int column, row;
    float offset = (60.0f * t);
    for(column = 0; column < columns; column++){
        hsv.h = (((float) column / (float) columns) * 360.0f) + offset;
        for(row = 0; row < rows; row++){
            strip->setPixelColor(row, column, hsv);
        }
    }
}

void Rainbow::buttonPress(uint8_t count){}

void Rainbow::dialRotate(uint8_t buttonClicks, int8_t dialClicks){}

