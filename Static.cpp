#include "Static.h"


Static::Static(int rows, int cols, Neopixel* strip) : Animation(rows, cols, strip){
    this->hue = 0.0f;
    this->saturation = 1.0f;
}

void Static::animate(float t, float dt){
    Neopixel::IntRGB rgb = Neopixel::convertToInt(Neopixel::hsv2rgb({hue, saturation, 1.0f}));
    int column, row;
    for(column = 0; column < columns; column++){
        for(row = 0; row < rows; row++){
            strip->setPixelColor(row, column, rgb);
        }
    }
}

void Static::buttonPress(uint8_t count){}

void Static::dialRotate(uint8_t buttonClicks, int8_t dialClicks){
    if(buttonClicks == 0){
        hue += dialClicks * 10.0f;
        if(hue < 0.0f){
            hue += 360.0f;
        }
    }else{
        saturation += dialClicks * 0.05f;
        if(saturation > 1.0f){
            saturation = 1.0f;
        }else if(saturation < 0.0f){
            saturation = 0.0f;
        }
    }
}
