#include "Stars.h"

Stars::Stars(int rows, int cols, Neopixel* strip) : Animation(rows, cols, strip){
    for(int i = 0; i < MAX_STARS; i++){
        stars[i].age = 1.0f;
        stars[i].maxAge = 0.0f;
    }
}

void Stars::animate(float t, float dt){

    numStars = (int) (param2 * MAX_STARS);
    
    Neopixel::IntRGB off = {0, 0, 0};
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < columns; col++){
            strip->setPixelColor(row, col, off);
        }
    }
    
    Neopixel::FloatHSV hsv = {param0 * 360.0f, param1, 1.0f};
    for(int i = 0; i < numStars; i++){
        if(stars[i].age > stars[i].maxAge){
            stars[i].age = 0.0f;
            stars[i].maxAge = random((int)(MIN_DURATION * 1000.0f), (int)(MAX_DURATION * 1000.0f)) / 1000.0f;
            stars[i].row = random(0, rows);
            stars[i].col = random(0, columns);
        }
        hsv.v = stars[i].age / (stars[i].maxAge / 2.0f);
        if(hsv.v > 1.0f){
            hsv.v = 2.0f - hsv.v;
        }
        strip->setPixelColor(stars[i].row, stars[i].col, hsv);
        stars[i].age += dt;
    }
}
