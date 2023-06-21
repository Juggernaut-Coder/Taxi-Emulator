#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define FIRST_REC_ID 1
#define MAX_CHARGE_PERCENTAGE 100
#define DEFAULT_CHARGE_RATE 3.2
#define FIRST_VIN_NUMBER 1000
/* Remove carriage return  */
#define TRUNCATE(name)	name[strlen(name)-1] = '\0'
/* Define the car structure */
typedef struct _Car {
    int VIN;
    float chargePercentage;
    float chargeRate;
    int totalDistanceTraveled;
    float totalChargeConsumed;
    int numberOfTrips;
    int rec_id;
} Car_rec;
/* Action the software needs to perform */
enum action {write_file,read_file};

int main(void) {
    int act;
    int VIN = FIRST_VIN_NUMBER;
    int loop_count;
    int rec_id = FIRST_REC_ID;
    printf("Enter 0 to write a new file or 1 to display a file:\n");
    scanf("%d", &act);
    
    if(act == write_file) {
        FILE *fp = fopen("CAR_REC.dat","w+b");
        printf("Please enter the number of vehicles you want to add:\n");
        scanf("%d%*c", &loop_count);
        FILE *rec_len = fopen("rec_length.txt", "w+");
        fprintf(rec_len, "%d \n", loop_count);
        fclose(rec_len);
        /* Create new record file */
        while(loop_count != 0) {
            Car_rec rec = {.VIN=VIN, .chargePercentage=MAX_CHARGE_PERCENTAGE, .chargeRate=DEFAULT_CHARGE_RATE, 
                           .totalDistanceTraveled=0, .totalChargeConsumed=0, .numberOfTrips=0, .rec_id=rec_id};
            fseek(fp, rec.rec_id * sizeof(Car_rec), SEEK_SET);
            fwrite(&rec, sizeof(Car_rec), 1, fp);
            rec_id++;
            VIN++;
            loop_count--;
        }
        fclose(fp);
    } else if (act == read_file) {
        FILE *fp = fopen("CAR_REC.dat","rb");
        FILE *rec_len = fopen("rec_length.txt", "r");
        fscanf(rec_len,"%d", &loop_count);
        fclose(rec_len);
        /* Print record file to screen*/
        while(loop_count != 0) {
            fseek(fp, rec_id*sizeof(Car_rec), SEEK_SET);
            Car_rec rec;
            fread(&rec, sizeof(Car_rec), 1, fp);
            printf("%d) VIN: %d, Charge percentage: %f, Charge rate: %f, Total distance: %d, Total charge consumed: %f, Number of trips: %d\n",
                rec_id, rec.VIN, rec.chargePercentage, rec.chargeRate, rec.totalDistanceTraveled, rec.totalChargeConsumed, rec.numberOfTrips
            );
            rec_id++;
            loop_count--;
        }
        fclose(fp);
    }
    
    return 0;
}