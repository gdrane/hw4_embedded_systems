// File includes
#include "mbed.h"
#include "pins.h"
#include "readInput.h"
#include "readSdfg.h"
#include "Graph.h"
#include "Node.h"
//#include "Scheduler.h"

#define DEBUG 1

// LED objects
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// USB Comm.
Serial pc(USBTX, USBRX);

// Local Filesystem
LocalFileSystem local("local");

int main() {
    // initialization
    pc.baud(115200);
    led1 = 1;
    // parse input file
    if(DEBUG)
        pc.printf("-- Parsing input.txt --\n\r");
    int x,k;
    readInput(&x,&k);
    if(DEBUG)
        pc.printf("X: %d, K: %d\n\r",x,k);
    // parse sdfg file
    if(DEBUG)
        pc.printf("-- Parsing sdfgconf.txt --\n\r");
    Graph* topology = ReadScheduleConfig();
    if(DEBUG)
        topology->Print();
    
    while(1) {     
    }
}
