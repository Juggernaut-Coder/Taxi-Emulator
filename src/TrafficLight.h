#ifndef   TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H



#include <math.h>
#include "MImage.h"
#include "Utils/vec.h"
#include "Trip.h"
#include "Utils/AStar/Graph.h"

typedef struct TrafficLight{
    MImage* img;
    // Vec2i pos;
    // Vec2i pXrowsCols[4];
    // Vec2i pYrowsCols[4];
    int row;
    int col;
    int status;
    float time;
    float countTime;
} TrafficLight;

TrafficLight* createTrafficLight(int row,int col,float time,int status){

    TrafficLight* c = (struct TrafficLight*)malloc( sizeof(TrafficLight));

    c->time = time;
    c->countTime = 0;

    c->status = status;
    c->row = row;
    c->col = col;

    // c->pXrowsCols[0] = newVec2(col-1,row );
    // c->pXrowsCols[1] = newVec2(col-1,row + 1 );
    // c->pXrowsCols[2] = newVec2(col + 2,row );
    // c->pXrowsCols[3] = newVec2 (col + 2,row + 1 );

    // c->pYrowsCols[0] = newVec2(col,row -1 );
    // c->pYrowsCols[1] = newVec2(col+1,row -1 );
    // c->pYrowsCols[2] = newVec2(col ,row + 2);
    // c->pYrowsCols[3] = newVec2(col +1,row + 2);



    return c;
}

void updateTrafficLight(TrafficLight* light){
    light->countTime += deltaTime;
    if(light->countTime >= light->time){
        light->countTime = 0;

        if(light->status == 0){
            light->status = 1;
        }
        else{
            light->status = 0;
        }
    }
}  

void drawTrafficLight(TrafficLight* light){

    for(int i = 0 ; i < 4;i++){
        lightImg->dest.x = light->col * 32;
        lightImg->dest.y = light->row * 32;

        // 0 -> x
        // 1 ->y
        if(light->status == 1){
            SDL_SetTextureColorMod(lightImg->texture,230,10,10);
        }
        else{
            SDL_SetTextureColorMod(lightImg->texture,10,230,10);
        }
        drawMImage(lightImg);
    }
}

#endif //    TRAFFIC_LIGHT_H