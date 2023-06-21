#ifndef  TRIP_H
#define TRIP_H



#include <math.h>
#include "MImage.h"
#include "Utils/vec.h"
#include "Building.h"

typedef struct Trip{
    Building* startBuilding;
    Building* endBuilding;
    char pickStart;
    char pickEnd;
    int status;
    int pickTime;


    // business
    int VIN;
    int PPN;
    int startTime;
    int endTime;
    float eneryConsume;
    int passengers;

    char* personName;
    char* email;

} Trip;

Trip* newTrip(Building* start,Building* end,char pickStart,char pickEnd,int pickTime,int passengers, char* personName,char* email){
    Trip* t = (struct Trip*)malloc( sizeof(Trip));
    t->startBuilding = start;
    t->endBuilding = end;
    t->pickStart = pickStart;
    t->pickEnd = pickEnd;
    t->status = 0;
    t->pickTime = pickTime;

    static int PPN = 100; PPN +=2;
    t->PPN = PPN;
    t->startTime = 0;
    t->endTime = 0;
    t->eneryConsume = 0;
    t->passengers = passengers;

    t->personName = personName;
    t->email = email; 

    return t;
}

Trip* getReadyTrip(vector* trips,int time){
    for(int i = 0 ; i < vector_total(trips);i++){
        Trip* t = (Trip*)vector_get(trips,i);
        // printf("timeclok: %d - %d\n",t->pickTime,time);
        if(t->status == 0 && t->pickTime <= time){
            return t;
        }
    }
    return NULL;
}
#endif //   TRIP_H