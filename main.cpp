// File includes
#include "mbed.h"
#include "pins.h"
#include "readInput.h"
#include "readSdfg.h"
#include "Edge.h"
#include "Graph.h"
#include "GraphTraveller.h"
#include "Node.h"
#include "Processor.h"
#include "Scheduler.h"

// LED objects
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// USB Comm.
Serial pc(p28, p27);

// Local Filesystem
LocalFileSystem local("local");

int main() {
    // initialization
    pc.baud(115200);
    led1 = 1;
    // parse input file
    pc.printf("-- Parsing input.txt --\n\r");
    int x,k;
    readInput(&x,&k);
    pc.printf("X: %d, K: %d\n\r",x,k);
    // parse sdfg file
    pc.printf("-- Parsing sdfgconf.txt --\n\r");
    Graph* topology = ReadScheduleConfig();
    
    while(1) {
        
    }
}
