#ifndef DB_H
#define DB_H

#include <stdio.h>
#include <stdlib.h>
#include "Trip.h"
#include <string.h>
#include "Car.h"
#include "Utils/vector.h"

#define MAX_TRIPS 256
static int count = 0;
float fare[MAX_TRIPS];
float chargeEachTrip[MAX_TRIPS];
int endtime[MAX_TRIPS];

void readTrips(vector* trips,vector* buildings){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    int read;

    fp = fopen("data/trips.txt", "r");
    if (fp == NULL){
        printf("trips file error!\n");
        return;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        // line
        // read format
        // start address, end address, start direction, end direction, time, number of passengers, name, email
        int startId = atoi(strtok(line, ","));
        int endId = atoi(strtok(NULL, ","));
        char pickStart = strtok(NULL, ",")[0];
        char pickEnd = strtok(NULL, ",")[0];
        int pickTime = atoi(strtok(NULL, ","));
        int passengers = atoi(strtok(NULL, ","));
        char* personName = strtok(NULL, ",");
        char* email = strtok(NULL, ",");

        Building* start = findBuilding(buildings,startId);
        Building* end = findBuilding(buildings,endId);
        if(start == NULL || end == NULL){
            printf("trips file error!\n");
            return;
        }
        Trip* trip = newTrip(start,end,pickStart,pickEnd,pickTime,passengers,personName,email);
        vector_add(trips,trip);
    }

    fclose(fp);
}   


void printCars(vector * cars){
    FILE *fp, *fp2;
    fp = fopen("data/cars.txt","w");
    fp2 = fopen("data/billing.txt","w");
    FILE *fp3 = fopen("data/trips.txt", "r");
    // Vehicle management information to be printed
    //   int VIN;/
    // float chargePercentage;/
    // float chargeRate;/
    // int totalDistanceTraveled;
    // float totalFareEarned;
    // int numberOfTrips;
    // Vec2i lastDestinationAddress;
    fprintf (fp, "VIN\t\tchargePercentage\t\tchargeRate\t\ttotalDistanceTraveled\t\ttotalFareEarned\t\tnumberOfTrips\t\tlastDestinationAddress\t\tStart time\t\t End time\t\t  active \t\t Total charge consumed\n");
    for (int i = 0; i < vector_total(cars); i++){ //cars
        Car* car = (Car*)vector_get(cars, i);
        if(car->type != 1){
            continue;
        }
        endtime[i] = car->end_time;
        fprintf (fp, "%d \t\t %f \t\t %f \t\t\t %d \t\t\t\t\t\t %f \t\t\t %d \t\t\t\t\t %d,%d,%c \t\t\t %d \t\t\t\t\t %d \t\t\t\t\t %d \t\t\t\t\t %f \n", 
            car->VIN,
            car->chargePercentage,
            car->chargeRate,
            car->totalDistanceTraveled,
            car->totalFareEarned,
            car->numberOfTrips,
            car->lastDestinationAddress.x,
            car->lastDestinationAddress.y,
            car->lastBuildingSide,
            car->start_time,
            car->end_time,
            car->active,
            car->totalChargeConsumed);
    }
    int i =0, read;
    size_t len = 0;
    char * line = NULL;
    int ppn = 100;
    int cnt = 0;
    int VIN = 1000;
    while ((read = getline(&line, &len, fp3)) != -1) {
        // line
        // read format
        // start address, end address, start direction, end direction, time, number of passengers, name, email
        int startId = atoi(strtok(line, ","));
        int endId = atoi(strtok(NULL, ","));
        strtok(NULL, ",");
        strtok(NULL, ",");
        int picktime = atoi(strtok(NULL, ","));
        int passengers = atoi(strtok(NULL, ","));
        char* personName = strtok(NULL, ",");
        char* email = strtok(NULL, ",");
        
        fprintf(fp2,"Customer Name: %s, Email: %s, PPN:%d\nPickup address: %d, Destination address: %d, Number of passengers: %d, VIN:%d, Charge consumed: %f Fare: %f, Pickup time:%d, End time:%d\n",personName,email,ppn,startId,endId,passengers,VIN,chargeEachTrip[i],fare[i],picktime,endtime[i]);
        fprintf(fp2,"\n");
        i++;
        ppn+=2;
        VIN++;
        cnt++;
        if(count == 3) {
            VIN = 1000;
            cnt = 0;
        }

    }
    
    fclose(fp);
    fclose(fp2);
    fclose(fp3);
}
#endif