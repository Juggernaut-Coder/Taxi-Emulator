#ifndef  TILE_H
#define TILE_H

#include "MImage.h"
#include "Utils/vec.h"

typedef struct Tile{
    MImage* img;
    Vec2i pos;

} Tile;

Tile* createTile(const char* filename, int x,int y){

    Tile* tile = (struct Tile*)malloc( sizeof(Tile));
    MImage* img = createMImage(filename,x,y,32,32);

    tile->pos.x = x;
    tile->pos.y = y;
    tile->img = img;

    return tile;
}
#endif //   TILE_H