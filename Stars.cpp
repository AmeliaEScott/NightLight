#include "Stars.h"

Stars::Stars(int rows, int cols, Neopixel* strip) : Animation(rows, cols, strip){
    for(int i = 0; i < MAX_STARS; i++){
        stars[i].age = 1.0f;
        stars[i].maxAge = 0.0f;
    }
}

void Stars::animate(float t, float dt){
    Neopixel::IntRGB off = {0, 0, 0};
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < columns; col++){
            strip->setPixelColor(row, col, off);
        }
    }
    
    Neopixel::FloatHSV hsv = {hue, saturation, 1.0f};
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
        char buff[100];
//        Serial.print(stars[i].age);
//        Serial.print(", ");
//        Serial.print(stars[i].maxAge);
//        Serial.print(", ");
//        Serial.println(hsv.v);
        stars[i].age += dt;
    }
}

void Stars::buttonPress(uint8_t count){}

void Stars::dialRotate(uint8_t buttonClicks, int8_t dialClicks){
    if(buttonClicks == 0){
        numStars += dialClicks;
        if(numStars < 0){
            numStars = 0;
        }else if(numStars > MAX_STARS){
            numStars = MAX_STARS;
        }
    }else if(buttonClicks == 1){
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

