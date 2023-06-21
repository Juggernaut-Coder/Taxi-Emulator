#ifndef CAR_H
#define CAR_H

#include <math.h>
#include "MImage.h"
#include "Utils/vec.h"
#include "Trip.h"
#include "Utils/AStar/Graph.h"
#include "TrafficLight.h"

typedef struct Car{
    MImage* img;
    Vec2i pos;
    int speed;
    int angle;
    Color color;
    vector targets;
    int currentTarget;
    float waitTime;
    int jam ;
    int removeJamTime;

    Trip* trip;
    float energy;
    int charTime;
    int status;
    int type;

        // bussiness
    int VIN;
    float chargePercentage;
    float chargeRate;
    int totalDistanceTraveled;
    float currentFare;
    float totalFareEarned;
    float totalChargeConsumed;
    int numberOfTrips;
    Vec2i lastDestinationAddress;
    char lastBuildingSide;
    int start_time;
    int end_time;
    int active;
} Car;

Car* createCar(const char* filename, int x,int y,int speed,int type){

    Car* car = (struct Car*)malloc( sizeof(Car));
    MImage* img = createMImage(filename,x,y,32,32);

    car->pos.x = x;
    car->pos.y = y;
    car->img = img;
    car->speed = speed;
    car->angle = 180;
    car->color = newColor(255,255,255);
    
    car->energy = 100;
    car->charTime = 0;
    car->status = 0;
    car->trip = NULL;

    vector_init(&car->targets);
    car->currentTarget = 0;
    car->waitTime = 0;
    car->type = type; // 1 : taxi, 
    car->jam = 0;
    car->removeJamTime = 0;


    // bussiness
    static int VIN = 1000; VIN += 1;
    car->VIN = VIN;
    car->chargePercentage = 100;
    car->chargeRate = 3.2;
    car->totalDistanceTraveled = 0;
    car->totalFareEarned = 0;
    car->totalChargeConsumed = 0;
    car->numberOfTrips = 0;
    car->currentFare = 0;
    car->lastDestinationAddress = newVec2(0,0);
    car->lastBuildingSide = '0';
    car->start_time = 0;
    car->end_time = 0;
    car->active = 0;
    return car;
}

int moveCarTo(Car*car,int toX, int toY)
{
	float disc = point_distance(car->pos.x, car->pos.y, toX, toY);

	float normalizedX = (toX - car->pos.x) / disc;
	float normalizedY = (toY - car->pos.y) / disc;

    int a = atan2(normalizedY, normalizedX)*180/PI;
    // if(abs(a- car->angle) > 10){
    //     car->angle = a;
    // }

    // printf("%d \n",car->angle);

	if (disc > 4) {
		car->pos.x += normalizedX * car->speed;
		car->pos.y += normalizedY * car->speed;
        if( a != car->angle){
            car->angle = a;
            // printf("angle: %d\n",car->angle);
        }
		return 0;
	}
	return 1;
}

int checkCarCollide(Car* car,GraphNode*** graphNodes,vector * othercars,vector* lights){
    (void)graphNodes;
    if(car->jam == 1){
        return 0;
    }
    if(car->currentTarget < vector_total(&car->targets) -1 ){
        Vec2i* nextTarget = (Vec2i*)vector_get(&car->targets, car->currentTarget +1 );
        // int nextRow = nextTarget->y ;
        // int nextCol = nextTarget->x ;

        // // target = (Vec2i*)vector_get(&car->targets, car->currentTarget + 1);
        // nextRow = nextTarget->y / 32;
        // nextCol = nextTarget->x / 32;
        // // printf("r: %d %d\n",nextRow,nextCol);
        // if(graphNodes[nextRow][nextCol]->c == 1){
        //     return 1;
        // }

        // printf("r: %d %d\n",nextRow,nextCol);

        float disc = point_distance(car->pos.x, car->pos.y, nextTarget->x, nextTarget->y);
        float normalizedX = (nextTarget->x - car->pos.x) / disc;
        float normalizedY = (nextTarget->y - car->pos.y) / disc;

        normalizedX = cos(car->angle * PI / 180);
        normalizedY = sin(car->angle * PI / 180);

        Vec2i* target = target = newVec2P(car->pos.x + normalizedX * 50,car->pos.y + normalizedY * 50);;
        for(int i = 0 ; i < vector_total(othercars);i++){
            Car* otherCar = (Car*) vector_get(othercars,i);
            if(otherCar == car){
                continue;
            }
            if(lineOnRect(car->pos.x + 16, car->pos.y + 16, target->x + 16 , target->y + 16,otherCar->img->dest.x,otherCar->img->dest.y,
            otherCar->img->dest.x + otherCar->img->dest.w ,otherCar->img->dest.y + otherCar->img->dest.h) == 1){
                return 1;
            }
        }
        for(int i = 0 ; i < vector_total(lights);i++){
            TrafficLight* light = (TrafficLight*) vector_get(lights,i);
            if(lineOnRect(car->pos.x + 16, car->pos.y + 16, target->x + 16 , target->y + 16,
             light->col * 32,light->row * 32,light->col * 32 + 32,light->row * 32 + 32) == 1){
                if(light->status == 1){
                    return 2;
                }
            }
        }
    }
    return 0;
}

void updateCar(Car* car,GraphNode*** graphNodes,vector * cars,vector* lights){
    car->img->dest.x = car->pos.x;
    car->img->dest.y = car->pos.y;


    if(car->pos.y >= 27 * 32 + 10){ // charge
        if(car->status == 10){
            car->waitTime += deltaTime;
        }
        car->charTime += deltaTime;
        if(car->charTime >= 200 && car->energy < 100){
            car->charTime = 0;
            car->energy += 1;
        }
    }

    if(car->currentTarget == vector_total(&car->targets)){
        if( vector_total(&car->targets) > 0){
            car->waitTime += deltaTime;
        }
        return;
    }

    Vec2i* target = (Vec2i*)vector_get(&car->targets, car->currentTarget);
    if(target == NULL){
        printf("null\n");
    }
    int collide = checkCarCollide(car,graphNodes,cars,lights);
    if(collide == 0){ // move if no collide
    // printf("%d - %d\n",target->x,target->y);
        if(moveCarTo(car,target->x,target->y) == 1){
            car->currentTarget++;
            car->waitTime = 0;

            // business
            car->totalDistanceTraveled += 1;
            car->energy -= 0.35;
            if(car->trip != NULL){
                car->trip->eneryConsume += 0.35;
            }
        }
    }
    else if(collide == 1){
        if(car->type > 1){
            car->waitTime += deltaTime;
            if(car->waitTime >= 5000){
                car->jam = 1;
            }
        }
    }

    if(car->type > 1 && car->jam == 1){
        car->removeJamTime += deltaTime;
        if(car->removeJamTime > 1000){
            car->removeJamTime = 0;
            car->jam = 0;
        }
    }

    car->img->dest.x = car->pos.x;
    car->img->dest.y = car->pos.y;
}



Car* getReadyCar(vector* cars){
    for(int i = 0 ; i < vector_total(cars);i++){
        Car* c = (Car*)vector_get(cars,i);
        if(c->status == 0 && c->type == 1 && c->active == 1 && c->energy > 25){
            return c;
        }
    }
    return NULL;
}

#endif // CAR_H