#include <vector>
#include <fstream>

#include "mbed.h"

#include "Graph.h"
#include "GraphTraveller.h"
#include "Node.h"
#include "Processor.h"
#include "Scheduler.h"

void PrintSdfgFormatError() {
    printf("ERROR: BAD SDFG FORMAT\n");
}

void ReadScheduleConfig() {
    FILE *fp = fopen("/local/sdfgconf.txt", "r");
    if(fp == NULL) {
        printf("ERROR: NO SDFG\n");
    }
    int noofnodes, noofedges;
    if(!feof(fp) && fscanf(fp, "%d %d" , &noofnodes, &noofedges) != 2) {
        PrintSdfgFormatError();       
    }
    
    fclose(fp);
}

bool CheckSchedulability() {

}

// -- Variables --
DigitalOut pin21(p21);
DigitalOut pin22(p22);
DigitalOut pin23(p23);

// -- Function Implementations --
void set(char pin){
    switch(pin){
        case 21:
            pin21 = 1;
            break;
        case 22:
            pin22 = 1;
            break;
        case 23:
            pin23 = 1;
            break;
        default:
            break;
    }
}
void clear(char pin){
    switch(pin){
        case 21:
            pin21 = 0;
            break;
        case 22:
            pin22 = 0;
            break;
        case 23:
            pin23 = 0;
            break;
        default:
            break;
    }
}


int main() {
    // Initializing pins 21, 22, 23 to zero
    pin21 = pin22 = pin23 = 0;
    while(1) {
    wait(0.2);
    }
    return 0;
}

