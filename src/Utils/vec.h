
#pragma once
#include <math.h>
#include <SDL2/SDL_ttf.h>

#define PI 3.14159265359

typedef struct Vec2i{
   int x;
   int y;
} Vec2i;

typedef struct Color{
   int r;
   int g;
   int b;
} Color;

Vec2i newVec2(int x,int y){
    Vec2i v;
    v.x = x;
    v.y = y;

    return v;
}

Color newColor(int r,int g,int b){
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;

    return c;
}

Vec2i* newVec2P(int x,int y){
    Vec2i* v = (struct Vec2i*)malloc( sizeof(struct Vec2i));
    v->x = x;
    v->y = y;
    return v;
}

float point_distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) +
		pow(y2 - y1, 2) * 1.0);
}

Vec2i getRowColFromPos(int width,int heigh,Vec2i pos){
    (void)width;
    (void)heigh;
    float sizeX = 32;
    float sizeY = 32;
    int row = pos.y / sizeY;
    int col = pos.x / sizeX;
    return newVec2(col,row);
}

Vec2i getRandomRoadPos(int width,int height,int ** grid){

    int row = rand() % height;
    int col = rand() % width;
    // printf("%d %d\n",row,col);
    while (grid[row][col] != 0)
    {
        // printf("%d %d\n",row,col);
        row = rand() % height;
        col = rand() % width;
    }
    return newVec2(col,row);
}

int lineOnRect(float x1, float y1, float x2, float y2, float minX, float minY, float maxX, float maxY) {  
    // Completely outside.
    if ((x1 <= minX && x2 <= minX) || (y1 <= minY && y2 <= minY) || (x1 >= maxX && x2 >= maxX) || (y1 >= maxY && y2 >= maxY))
        return 0;

    float m = (y2 - y1) / (x2 - x1);

    float y = m * (minX - x1) + y1;
    if (y > minY && y < maxY) return 1;

    y = m * (maxX - x1) + y1;
    if (y > minY && y < maxY) return 1;

    float x = (minY - y1) / m + x1;
    if (x > minX && x < maxX) return 1;

    x = (maxY - y1) / m + x1;
    if (x > minX && x < maxX) return 1;

    return 0;
}


// text
TTF_Font* font; 
SDL_Surface* surface = NULL;
SDL_Texture* texture = NULL;
void showText(int x, int y, const char* text, int r,int g,int b ) {

    SDL_Color fg ;
    fg.r = r;fg.g = g;fg.b = b;

    surface = TTF_RenderText_Solid(font, text, fg);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect srcRest;
    SDL_Rect desRect;
    TTF_SizeText(font, text, &srcRest.w, &srcRest.h);

    srcRest.x = 0;
    srcRest.y = 0;

    desRect.x = x;
    desRect.y = y;

    desRect.w = srcRest.w;
    desRect.h = srcRest.h;
    SDL_RenderCopy(renderer, texture, &srcRest, &desRect);

    SDL_DestroyTexture(texture);
}