#ifndef  MImage_H
#define MImage_H



#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "Utils/vec.h"


typedef struct MImage{
    SDL_Texture* texture;
    SDL_Rect    src;
    SDL_Rect    dest;
    SDL_Point center;
    float angle;
} MImage;

MImage* createMImage(const char* path,int x,int y,int w,int h){
   MImage* mImage = (struct MImage*)malloc( sizeof(struct MImage));
    

    mImage->texture = SDL_CreateTextureFromSurface(renderer, IMG_Load(path));
    mImage->src.x = 0;
    mImage->src.y = 0;
    mImage->src.w = w;
    mImage->src.h = h;

    mImage->dest.x = x;
    mImage->dest.y = y;
    mImage->dest.w = w;
    mImage->dest.h = h;

    return mImage;
}

void drawMImage(MImage* mImage){
    SDL_RenderCopy(renderer, mImage->texture, NULL, &mImage->dest);
}
void drawMImageEx(MImage* mImage,float angle,Color color){
    SDL_SetTextureColorMod(mImage->texture,color.r,color.g,color.b);
    SDL_RenderCopyEx(renderer,
                    mImage->texture,
                    NULL,
                    &mImage->dest,
                    angle,
                    NULL,
                   SDL_FLIP_NONE);
                   
}


MImage* left = NULL;
MImage* right = NULL;
MImage* up = NULL;
MImage* down = NULL;
MImage* lightImg = NULL;

#endif //   MImage_H