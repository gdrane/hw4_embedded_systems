// File includes
#include "mbed.h"
#include "pins.h"
#include "readInput.h"
#include "readSdfg.h"
#include "Graph.h"
#include "Node.h"
#include "Scheduler.h"
#include "Edge.h"

// LED objects
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// USB Comm.
Serial pc(USBTX, USBRX);

// Timer
Timer t;

// Local Filesystem
LocalFileSystem local("local");

int main() {
    // -- initialization --
    pc.baud(115200);
    int timeElapsed = 0;
    t.start();
    // -- parse sdfg file --
    Graph* topology = ReadScheduleConfig();
    topology->Print();
    // -- schedulability test --
    Scheduler* scheduler = new Scheduler(topology);
    bool scheduled = scheduler->isSchedulable();
    timeElapsed = t.read_ms();
    if(scheduled){
        pc.printf("SCHEDULE: ");
        int* schedule = scheduler->getSchedule();
        int schedLen = scheduler->getScheduleLength();
        for(int i=0; i<schedLen; i++){
            pc.printf("%c%d ",topology->getNode(schedule[i])->get_node_id(), schedule[i]);
        }
    }else{
        pc.printf("NOT SCHEDULABLE\n\r");
    }
    led1 = 1;
    // set pin 21 for grading purposes
    set(21);
    pc.printf("\n\rReady @ %d\n\r",timeElapsed);
    
    // -- parse input file --
    int x,k;
    readInput(&x,&k);
    
    while(1) {
        // do nothing forever, and be good at it!
    }
}
