#include "Rainbow.h"

#define SPEED_SCALE 2000.0f
#define HUE_SCALE 100.0f

void Rainbow::animate(long t, float dt){
    Neopixel::FloatHSV hsv = {0.0f, param1, 1.0f};
    int column, row;
    if(!stopped){
        offset += (param0 * SPEED_SCALE * dt);
    }
    for(column = 0; column < columns; column++){

        for(row = 0; row < rows; row++){
            float dist = sqrt(sq(row - (rows - 1) * 0.5f) + sq(column - (columns - 1) * 0.5f));
            hsv.h = (dist * param2 * HUE_SCALE) + offset;
            strip->setPixelColor(row, column, hsv);
        }
    }
}
