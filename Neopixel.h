#include <Adafruit_NeoPixel.h>

#ifndef NEOPIXEL_H
#define NEOPIXEL_H

class Neopixel : public Adafruit_NeoPixel {
public:
    typedef struct FloatRGB {
        float r;
        float g;
        float b;
    } FloatRGB;
    
    typedef struct FloatHSV {
        float h;
        float s;
        float v;
    } FloatHSV;
    
    typedef struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } IntRGB;
    
    Neopixel(uint16_t rows, uint16_t cols, uint8_t p, uint8_t t);
    void setPixelColor(uint16_t row, uint16_t col, FloatHSV hsv);
    void setPixelColor(uint16_t row, uint16_t col, FloatRGB rgb);
    void setPixelColor(uint16_t row, uint16_t col, IntRGB rgb);
    uint16_t getLocation(uint16_t row, uint16_t col);

    static FloatRGB hsv2rgb(FloatHSV in);
    static IntRGB convertToInt(FloatRGB in);
private:
    uint16_t rows, cols;
};

#endif
