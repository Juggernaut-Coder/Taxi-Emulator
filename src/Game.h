#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "MImage.h"
#include "Clock.h"
#include "Map.h"

struct MImage*  mImage1;
struct MImage*  mImage2;

void gameStart(){
    mImage1 = createMImage( "images/car1.png",250,250,32,32);
    mImage2 = createMImage( "images/car1.png",650,250,32,32);

    createMap();
}

void gameUpdate(){
    updateMap();
}

void gameDraw(){
    // drawMImage(mImage1); // draw image 1
    // drawMImage(mImage2); // draw image 2

    drawMap();
}

#endif //  GAME_H