#ifndef PROCESSOR_H
#define PROCESSOR_H
class Processor {
    public:
        void OneClockTick() {
            // Travel through the graph and process all the graph nodes
            GraphTraveller::GetInstance()->TravelGraph();
        }
};
#endif
