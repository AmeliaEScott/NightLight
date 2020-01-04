#include "Neopixel.h"
#include <math.h>

Neopixel::Neopixel(uint16_t rows, uint16_t cols, uint8_t p, uint8_t t) : Adafruit_NeoPixel(rows * cols, p, t){
    //Adafruit_NeoPixel(rows * cols, p, t);
    this->rows = rows;
    this->cols = cols;
}

void Neopixel::setPixelColor(uint16_t row, uint16_t col, FloatHSV hsv){
    setPixelColor(row, col, hsv2rgb(hsv));
}

void Neopixel::setPixelColor(uint16_t row, uint16_t col, FloatRGB rgb){
    IntRGB intrgb = convertToInt(rgb);
    setPixelColor(row, col, intrgb);
}

void Neopixel::setPixelColor(uint16_t row, uint16_t col, IntRGB rgb){
    Adafruit_NeoPixel::setPixelColor(getLocation(row, col), rgb.r, rgb.g, rgb.b);
}

uint16_t Neopixel::getLocation(uint16_t row, uint16_t col){
    return cols * row + col;
}

// Code adapted from https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
Neopixel::FloatRGB Neopixel::hsv2rgb(Neopixel::FloatHSV in)
{
    float       hh, p, q, t, ff;
    long        i;
    Neopixel::FloatRGB out;
    in.h = fmod(in.h, 360.0f);
    if(in.h < 0.0f){
        in.h += 360.0f;
    }

    if(in.s <= 0.001f) {
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0f) hh = 0.0f;
    hh /= 60.0f;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0f - in.s);
    q = in.v * (1.0f - (in.s * ff));
    t = in.v * (1.0f - (in.s * (1.0f - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;     
}

Neopixel::IntRGB Neopixel::convertToInt(Neopixel::FloatRGB in){
    IntRGB out;
    out.r = (uint8_t)(255.0f * in.r);
    out.g = (uint8_t)(255.0f * in.g);
    out.b = (uint8_t)(255.0f * in.b);
    return out;
}
