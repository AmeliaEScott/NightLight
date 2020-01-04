#include "Static.h"


Static::Static(int rows, int cols, Neopixel* strip) : Animation(rows, cols, strip){
}

void Static::animate(long t, float dt){
    Neopixel::IntRGB rgb = Neopixel::convertToInt(Neopixel::hsv2rgb({param0 * 360.0f, param1, 1.0f}));
    int column, row;
    for(column = 0; column < columns; column++){
        for(row = 0; row < rows; row++){
            strip->setPixelColor(row, column, rgb);
        }
    }
}
