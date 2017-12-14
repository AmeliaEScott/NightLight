#include "Wave.h"
#include <math.h>


Wave::Wave(int rows, int cols, Neopixel* strip) : Animation(rows, cols, strip){
    this->hue = 0.0f;
}

void Wave::animate(float t, float dt){
    //Neopixel::FloatHSV hsv = {hue, 1.0f, 1.0f};
    Neopixel::IntRGB rgb = Neopixel::convertToInt(Neopixel::hsv2rgb({hue, 1.0f, 1.0f}));
    Neopixel::IntRGB off = {0, 0, 0};
    int column, row, top;
    float colFrac = 0.0f;
    for(column = 0; column < columns; column++){
        colFrac = (column / (float) columns) * 4 * PI;
        top = (int)((cos(colFrac) / 2.0f + 0.5f) * rows);
        for(row = 0; row < top; row++){
            strip->setPixelColor(row, column, rgb);
        }
        for(row = top; row < rows; row++){
            strip->setPixelColor(row, column, off);
        }
    }
}

void Wave::buttonPress(uint8_t count){}

void Wave::dialRotate(uint8_t buttonClicks, int8_t dialClicks){
    hue += dialClicks * 10.0f;
    if(hue < 0.0f){
        hue += 360.0f;
    }
}
