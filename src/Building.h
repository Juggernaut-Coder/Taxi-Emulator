#ifndef BUILDING_H
#define BUILDING_H

#include <math.h>
#include "MImage.h"
#include "Utils/vec.h"

typedef struct Building{
    int row;
    int col;
    int width;
    int height;
    int id;
} Building;



Building* createBuilding(int row,int col,int width,int height,int id){
    Building* b = (struct Building*)malloc( sizeof(struct Building));

    b->row = row;
    b->col = col;
    b->width = width;
    b->height = height;
    b->id = id;

    return b;
}

Vec2i getNorth(Building* b){
    return newVec2(b->col,b->row-1);
}
Vec2i getSouth(Building* b){
    return newVec2(b->col, b->row + b->height);
}
Vec2i getWest(Building* b){
    return newVec2(b->col-1, b->row );
}
Vec2i getEast(Building* b){
    return newVec2(b->col + b->width, b->row );
}

Building* findBuilding(vector* buildings,int id){
    for(int i = 0 ; i < vector_total(buildings);i++){
        Building* b = (Building*)vector_get(buildings,i);
        if(b->id == id){
            return b;
        }
    }
    return NULL;
}

Vec2i getBuildingPos(Building* b,char pick){
    if(pick == 'S'){
        return getSouth(b);
    }
    else if(pick == 'N'){
        return getNorth(b);
    }
    else if(pick == 'W'){
        return getWest(b);
    }
    else if(pick == 'E'){
        return getEast(b);
    }
    return newVec2(0,0);
}

#endif //  BUILDING_H