
#ifndef MAP_H
#define MAP_H

//#define NPC_CAR 3



#include <stdlib.h>
#include "Utils/vector.h"
#include "Tile.h"
#include "Car.h"
#include "Utils/AStar/AStar.h"
#include "Building.h"
#include "DB.h"
#include "TrafficLight.h"
// #include "Utils/AStar/Graph.h"

int** graphData1_p;
vector tiles;
vector cars;
vector buildings;
int startTime = 0;
vector trips;
vector lights;
Astar* astar ;
int tileSize = 32;
int waitTime = 0;
int timeClock = 0;
float countTime = 0;

int const rows = 33;
int const cols = 60;

int tripsDone = 0;
int k = 0;



void npcCarLogic(Car* car);

void createMap(){
    // create arrows
    left = createMImage("images/al.png",0,0,10,10);
    right = createMImage("images/ar.png",0,0,10,10);
    up = createMImage("images/au.png",0,0,10,10);
    down = createMImage("images/ad.png",0,0,10,10);
    lightImg = createMImage("images/road.png",0,0,32,32);


    // arrays
    vector_init(&tiles);
    vector_init(&cars);
    vector_init(&buildings);
    vector_init(&trips);
    vector_init(&lights);

    int graphData1[33][60] = {
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5}, 
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,4,4,0,0,4,4,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,5},
        {5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5},
        {5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5},
        {5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5},
        {5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5},
        {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
    };

    // setup building

    //  
    int bR = 3;
    int bC = 3;
    int buildingId = 0;
    for(int row = 0;row < 4;row++){
        for (int col = 0; col < 6;col++){
            Building* b1 = createBuilding(bR,bC,2,2,buildingId);vector_add(&buildings,b1);
            bC += 10;
            buildingId++;
        }
        bC = 3;
        bR += 7;
    } 

    for(int i = 0 ; i < vector_total(&buildings);i++){
        Building* b = (Building*) vector_get(&buildings,i);
        for(int r  = b->row ; r < b->row + b->height;r++){
            for (int c = b->col; c < b->col + b->width;c++){
                graphData1[r][c] = 2;
            }
        }
    }

    // setup road

    //setup graph
    graphData1_p = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        graphData1_p[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            graphData1_p[i][j] = graphData1[i][j];
        }
    }
    //setup tiles
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {

            if (graphData1[row][col] == 0) {
                Tile * road = createTile("images/road.png",col * tileSize, row * tileSize);
                vector_add(&tiles,road);
            }
            else if (graphData1[row][col] == 5) {
                Tile * grass = createTile("images/dirt.png",col * tileSize, row * tileSize);
                vector_add(&tiles,grass);
            }
            else if (graphData1[row][col] == 4) {
                Tile * grass = createTile("images/grass.png",col * tileSize, row * tileSize);
                vector_add(&tiles,grass);
            }
             else if (graphData1[row][col] == 2) {
                Tile * grass = createTile("images/building.png",col * tileSize, row * tileSize);
                vector_add(&tiles,grass);
            }

        }
    }

    readTrips(&trips,&buildings);

    //setup car

    // taxi
    Car * car = createCar("images/car1.png",827,31*32,5,1);car->active = 1;
    vector_add(&cars,car);
    Car * car2 = createCar("images/car1.png",903,31*32,5,1);car2->active = 1;
    vector_add(&cars,car2);
    Car * car3 = createCar("images/car1.png",950,31*32,5,1);car3->active = 1;
    vector_add(&cars,car3);
    Car * car4 = createCar("images/car1.png",1010,31*32,5,1);car4->active = 1;
    vector_add(&cars,car4);


    for(int i = 0 ; i < 16;i++){ // company taxi inactive cars
        Car * car = createCar("images/car1.png",(33 + k) *32,31 *32,5,1);car->active = 0;
        car->color = newColor(rand()%255,rand()%255,rand()%255);
        vector_add(&cars,car);
        k++;
    }
    #ifdef NPC_CAR
    for(int i = 0; i < NPC_CAR;i++){
        Vec2i v = getRandomRoadPos(cols,rows,graphData1_p);
        int type = 2 + rand() % 3;
        int speed = 2 + (rand() % 3);
        speed = 5;
        // printf("type: %d\n",type);
        // printf("speed: %d\n",speed);
        Car * carN;
        if (type == 2){
            carN = createCar("images/car2.png",v.x * 32,v.y * 32,speed,type);
        }
        else if (type == 3){
            carN = createCar("images/car3.png",v.x * 32,v.y * 32,speed,type);
        }
        else if (type == 4){
            carN = createCar("images/car4.png",v.x * 32,v.y * 32,speed,type);
        }
        vector_add(&cars,carN);
    }
    #endif
    Graph* graph = createGraph(cols,rows,graphData1_p);
    astar = createAstar(graph);


    // init traffic lights
    TrafficLight * light1 = createTrafficLight(15,20,2000,0);vector_add(&lights,light1);
    TrafficLight * light2 = createTrafficLight(16,20,2000,1);vector_add(&lights,light2);
    light1 = createTrafficLight(15,37,2000,0);vector_add(&lights,light1);
    light2 = createTrafficLight(16,37,2000,1);vector_add(&lights,light2);
    light1 = createTrafficLight(7,35,2000,0);vector_add(&lights,light1);
    light2 = createTrafficLight(7,36,2000,1);vector_add(&lights,light2);

    light1 = createTrafficLight(5,14,2000,0);vector_add(&lights,light1);
    light2 = createTrafficLight(6,14,2000,1);vector_add(&lights,light2);

    
}

void onMapClick(int x,int y){
   
    for (int i = 0; i < vector_total(&cars); i++){ //cars
        Car* car = (Car*)vector_get(&cars, i);

        if(car->type == 1 && car->active == 0){
            if(x  >= car->img->dest.x && x <=  car->img->dest.x +  car->img->dest.w
            && y  >= car->img->dest.y && y  <=  car->img->dest.y +  car->img->dest.h){
                vector_delete(&cars,i);
                k--;
            }
        }
    }

    int t = 0;
    for(int i = 0 ; i < vector_total(&cars);i++){ 
        Car* car = (Car*)vector_get(&cars, i);
        if(car->type == 1 && car->active == 0){
            car->pos.x = (33 + t) * 32;
            car->img->dest.x = car->pos.x;
            car->img->dest.y = car->pos.y;
            t++;    
        }
    }
}

void onKeyClick(int key){
    if(key == 49){ // 1
        printCars(&cars);
        printf("cars printed! \n");
    }
    if(key == 50){
        Car * car = createCar("images/car1.png",(33 + k) *32,31 *32,5,1);car->active = 0;
        car->color = newColor(rand()%255,rand()%255,rand()%255);
        vector_add(&cars,car);
        k++;
    }


}

void updateMap(){
    // waitTime += deltaTime;
    // waitTime = 0;
    Trip* readyTrip = getReadyTrip(&trips,timeClock);
    Car* readyCar = getReadyCar(&cars);

    // if(readTrips == NULL){
    //     printf("null trip\n");
    // }
    // if(readyCar == NULL){
    //     printf("null car\n");
    // }

    if(readyTrip != NULL && readyCar != NULL){ // start trip
        readyCar->status = 1;
        readyTrip->status = 1;
        readyCar->trip = readyTrip;
        Vec2i startPos = getRowColFromPos(33,60,newVec2(readyCar->pos.x,readyCar->pos.y));
        Vec2i endPos = getBuildingPos(readyTrip->startBuilding,readyTrip->pickStart);
        // printf("pickup: %d %d\n",endPos.y,endPos.x);
        vector_free(&readyCar->targets);
        vector_init(&readyCar->targets);
        readyCar->currentTarget = 0;
        aStarFinding(astar,&readyCar->targets,startPos,endPos);

        //business
        readyCar->trip->startTime = timeClock;
        startTime= timeClock;
        
    }
    if( tripsDone >= vector_total(&trips) && readyCar != NULL && readyCar->status != 10 ){ // all trip done
        // printf("all trips done!\n");
        if(readyCar->trip != NULL && readyCar->trip->status == 3  ){
            Vec2i pos = getBuildingPos(readyCar->trip->endBuilding,readyCar->trip->pickEnd);
            if( readyCar->pos.y  < 27 * 32 ){
                readyCar->pos.x = pos.x * 32;
                readyCar->pos.y = pos.y * 32;
            }

        }
        readyCar->waitTime = 0;
        Vec2i startPos = getRowColFromPos(33,60,newVec2(readyCar->pos.x,readyCar->pos.y));
        Vec2i endPos = newVec2(25,31);
        vector_free(&readyCar->targets);
        vector_init(&readyCar->targets);
        readyCar->currentTarget = 0;
        readyCar->status = 10; // return
        aStarFinding(astar,&readyCar->targets,startPos,endPos);

    }

    for (int i = 0; i < vector_total(&cars); i++){ //cars
        Car* car = (Car*)vector_get(&cars, i);
        
        if(car->active == 0 && car->type == 1){
            continue;
        }

        // if(car->type == 1 && i != 0){
        //     continue;
        // }
        #ifdef NPC_CAR
        if(car->type != 1){
            npcCarLogic(car);
        }
        #endif
        if(car->speed == 0){
            printf("speed 0\n");
        }
        
        if(car->waitTime >= 1000 && car->status == 1){ // pick passenger
            car->waitTime = 0;
            car->trip->status = 2;
            car->status = 2; // 
            car->color = newColor(255,12,12);
            Vec2i startPos = getRowColFromPos(33,60,newVec2(car->pos.x,car->pos.y));
            car->lastBuildingSide = car->trip->pickEnd;
            Vec2i endPos = getBuildingPos(car->trip->endBuilding,car->trip->pickEnd);
            car->start_time = timeClock-8;
            vector_free(&car->targets);
            vector_init(&car->targets);
            car->currentTarget = 0;
            aStarFinding(astar,&car->targets,startPos,endPos);
        }
        if(car->waitTime >= 1000 && car->status == 2){ //  trip finish
            car->status = 0;
            car->waitTime = 0;
            car->trip->status = 3;
            car->color = newColor(255,255,255);
            tripsDone++;

            if(car->energy <= 25){ // go back to charge
                car->waitTime = 0;
                Vec2i startPos = getRowColFromPos(33,60,newVec2(car->pos.x,car->pos.y));
                Vec2i endPos = newVec2(25,31);
                vector_free(&car->targets);
                vector_init(&car->targets);
                car->currentTarget = 0;
                car->status = 10; // return
                aStarFinding(astar,&car->targets,startPos,endPos);
            }
           
            // business
            car->trip->endTime = timeClock;
            car->end_time = timeClock;
            car->numberOfTrips++;
            car->lastDestinationAddress = newVec2(car->pos.x /32,car->pos.y / 32);
            car->currentFare = car->trip->eneryConsume * 5;
            fare[count] = car->currentFare;
            chargeEachTrip[count] = car->trip->eneryConsume;
            count++;
            car->totalChargeConsumed += car->trip->eneryConsume;
            car->totalFareEarned += car->currentFare;
            car->chargePercentage = car->energy;
            printCars(&cars);
        }
        if(car->status == 10 && car->energy < 100){
            if(car->energy >= 99){
                car->status = 0;
            }
            car->waitTime = 0;
        }
        if(car->trip != NULL && car->trip->status == 3 && car->status != 10 && car->waitTime >= 1000){
            if(car->pos.y < 27 * 32 ){
                car->pos.x = car->trip->endBuilding->col * 32;
                car->pos.y = car->trip->endBuilding->row * 32;
            }
            car->status = 0;
        }

        updateCar(car,astar->graphData->graphNodes,&cars,&lights);
    }

    for (int i = 0; i < vector_total(&lights); i++){ // tiles
        TrafficLight* light = (TrafficLight*)vector_get(&lights, i);
        updateTrafficLight(light);
    }

    // time
    countTime += deltaTime;
    if(countTime > 1000){
        countTime = 0;
        timeClock++;
    }
}

void npcCarLogic(Car* car){
    if(car->currentTarget == vector_total(&car->targets) || car->waitTime >= 1000){
        Vec2i startPos = getRowColFromPos(rows,cols,newVec2(car->pos.x,car->pos.y));
        Vec2i endPos = getRandomRoadPos(cols,rows,graphData1_p);
        vector_free(&car->targets);
        vector_init(&car->targets);
        car->currentTarget = 0;
        car->speed = 5;
        aStarFinding(astar,&car->targets,startPos,endPos);
    }
}


void drawMap(){
    for (int i = 0; i < vector_total(&tiles); i++){ // tiles
        Tile* tile = (Tile*)vector_get(&tiles, i);
        drawMImage(tile->img);
    }

    for (int i = 0; i < vector_total(&lights); i++){ // tiles
        TrafficLight* light = (TrafficLight*)vector_get(&lights, i);
        drawTrafficLight(light);
    }

    drawArrows(astar->graphData->graphNodes,rows,cols,left,right,up,down);

    for (int i = 0; i < vector_total(&cars); i++){ //cars
        Car* car = (Car*)vector_get(&cars, i);
        drawMImageEx(car->img,car->angle + 90,car->color);

        if(car->type == 1){
            char energyStr[100];
            sprintf(energyStr, "%.f", car->energy);
            showText(car->pos.x + 6,car->pos.y + 6,energyStr,255,255,22);
        }
       
    }

    for (int i = 0; i < vector_total(&buildings); i++){ // tiles
        Building* building = (Building*)vector_get(&buildings, i);
        char idStr[100];
        sprintf(idStr, "%d", building->id);
        showText(building->col * 32 + 22,building->row * 32 + 18,idStr,22,22,22);
    }

    // show texts
    char strTime[200] = "Time: ";
    char timeClockStr[100];
    sprintf(timeClockStr, "%d", timeClock);
    strcat(strTime,timeClockStr);
    showText(250,900,strTime,123,255,123);

}

#endif //  MAP_H