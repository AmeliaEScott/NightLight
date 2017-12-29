#include <Adafruit_NeoPixel.h>

#ifndef NEOPIXEL_H
#define NEOPIXEL_H

/**
 * An extension of the Adafruit_NeoPixel class, which adds some convenience.
 */
class Neopixel : public Adafruit_NeoPixel {
public:
    /**
     * Represents an RGB triplet with values between 0.0 and 1.0
     */
    typedef struct FloatRGB {
        float r;
        float g;
        float b;
    } FloatRGB;

    /**
     * Represents an HSV triplet with values between 0.0 and 1.0
     */
    typedef struct FloatHSV {
        float h;
        float s;
        float v;
    } FloatHSV;

    /**
     * Represents an RGB triplet with integer values between 0 and 255
     */
    typedef struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } IntRGB;
    
    Neopixel(uint16_t rows, uint16_t cols, uint8_t p, uint8_t t);
    void setPixelColor(uint16_t row, uint16_t col, FloatHSV hsv);
    void setPixelColor(uint16_t row, uint16_t col, FloatRGB rgb);
    void setPixelColor(uint16_t row, uint16_t col, IntRGB rgb);

    /**
     * Returns the location (the number of pixels along the strand) of the given
     * (row, col) pair.
     */
    uint16_t getLocation(uint16_t row, uint16_t col);

    /**
     * Converts HSV colors to RGB.
     */
    static FloatRGB hsv2rgb(FloatHSV in);

    /**
     * Converts Float RGBs (between 0.0 and 1.0) to integer RGBs (between 0 and 255).
     */
    static IntRGB convertToInt(FloatRGB in);
private:
    uint16_t rows, cols;
};

#endif
