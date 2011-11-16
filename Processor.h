#ifndef PROCESSOR_H
#define PROCESSOR_H

#define MAX_BUFFER_SIZE 4096

#include "Graph.h"
#include "Scheduler.h"

// -- Variables --
signed long outBuffer[MAX_BUFFER_SIZE] __attribute__ ((section("AHBSRAM1"))); 

class Processor {
    public:
        Processor(Graph* topology, Scheduler* scheduler, int buff_length) {
            _topology = topology;
            _scheduler = scheduler;
            _out_buffer_counter = 0;
            _in_buffer_length = buff_length;
        }
        
        void RunProcess() {
            while(_cur_buf_count < _in_buffer_length) {
                // Execute one clock according to schedule
                ExecuteSchedule();
            }
        }
        void ExecuteSchedule() {
            // Execute As per the schedule
            int* schedulearr = _scheduler->getSchedule();
            for(int i = 0; i < _scheduler->getScheduleLength(); ++i) {
                if(_topology->getNode(schedulearr[i])->get_node_id() == 'I') {
                 // Push input to the I node, Edge 0 is input to Node I
                _topology->getEdge(0)->push(inBuffer[_cur_buf_count++]);
               }
                _topology->processNode(schedulearr[i]);
                // check to see if output has been reached yet
                if(_topology->getNode(schedulearr[i])->get_node_id() == 'O') {
                    // Pull output to the O node, Edge numnodes + 1 outputs to Node O
                    outBuffer[_out_buffer_counter] = _topology->getEdge(_topology->getNumNodes() + 1)->pop();
                    pc.printf("%d\n\r", outBuffer[_out_buffer_counter]);
                    _out_buffer_counter = (_out_buffer_counter + 1) % MAX_BUFFER_SIZE;
                }
            }
            
        }
        
        void SetInBuffer(int *inBuffer) {
            _in_buffer = inBuffer;
            _cur_buf_count = 0;
        }
        
        
    private:
        Graph *_topology;
        Scheduler *_scheduler;
        int *_in_buffer;    
        int _out_buffer_counter;
        int _in_buffer_length;
        int _cur_buf_count;
};
#endif
