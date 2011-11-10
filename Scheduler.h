#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include <vector>

#include "Graph.h"
 
using namespace std;

class Scheduler {
    public:
        string GenerateSchedule(Graph* topology) {
            // Algorithm that generates the schedule
        }
        string GetScheduleToPrint() { 
            return _schedule_to_print;
        }
        vector<int> schedule() {
            return _schedule;
        }
         
    private:
        string _schedule_to_print;
        vector<int> _schedule;
};
#endif
