#include "Rainbow.h"

void Rainbow::animate(float t, float dt){
    Neopixel::FloatHSV hsv = {0.0f, 1.0f, 0.05f};
    int location, column, row;
    //Serial.print("Rainbow, time ");
    //Serial.println(t);
    float offset = (60.0f * t);
    for(column = 0; column < columns; column++){
        hsv.h = (((float) column / (float) columns) * 360.0f) + offset;
        for(row = 0; row < rows; row++){
            location = columns * row + column;
            strip->setPixelColor(row, column, hsv);
        }
    }
}

