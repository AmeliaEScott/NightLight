#include "Clock.h"

static constexpr uint32_t digitDisplay[10] = {
    0b0111001010010100101001110,
    0b0010000100001000010000100,
    0b0111000010011100100001110,
    0b0111000010011100001001110,
    0b0101001010011100001000010,
    0b0111001000011100001001110,
    0b0111001000011100101001110,
    0b0111000010000100001000010,
    0b0111001010011100101001110,
    0b0111001010011100001000010
};

Clock::Clock(int rows, int cols, Neopixel* strip) : Animation(rows, cols, strip){
}

void Clock::animate(long t, float dt){
    Neopixel::IntRGB rgbOn = Neopixel::convertToInt(Neopixel::hsv2rgb({param0 * 360.0f, 1.0f, 1.0f}));
    Neopixel::IntRGB rgbOff = Neopixel::convertToInt(Neopixel::hsv2rgb({param0 * 360.0f, 1.0f, 0.0f}));

    long minutes = (t / (1000l * 60l));
    long hours = (t / (1000l * 60l * 60l));

    int minutesOffset = (int) (param2 * 60.0f);
    int hoursOffset = (int) (param1 * 12.0f);

    int minutesDisplay = (minutes + minutesOffset) % 60;
    int hoursDisplay = (hours + hoursOffset) % 12 + 1;

    // Serial.print("(");
    // Serial.print(t);
    // Serial.print(") ");
    // Serial.print(hoursDisplay);
    // Serial.print(":");
    // Serial.print(minutesDisplay);
    // Serial.println();

    int digits[4] = {
        (minutesDisplay / 10) % 10, minutesDisplay % 10,
        (hoursDisplay / 10) % 10, hoursDisplay % 10
    };

    for(int digitRow = 0; digitRow < 2; digitRow++){
        for(int digitCol = 0; digitCol < 2; digitCol++){
            int digit = digits[digitRow * 2 + digitCol];
            for(uint32_t row = 0; row < 5; row++){
                for(uint32_t col = 0; col < 5; col++){
                    int displayRow = digitRow * 5 + row;
                    int displayCol = digitCol * 5 + col;
                    if(digitDisplay[digit] & (1l << (row * 5 + (4 - col)))){
                        strip->setPixelColor(displayRow, displayCol, rgbOn);
                    }else{
                        strip->setPixelColor(displayRow, displayCol, rgbOff);
                    }
                }
            }
        }
    }
}
