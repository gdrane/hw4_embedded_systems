#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>

#include "Graph.h"
#include "Node.h"

#define MAX_SCHED_LEN 128

using namespace std;
class Scheduler {
    public:
        // variables
        int _schedule[MAX_SCHED_LEN];
        
        bool isSchedulable(Graph* topology){
            /* Iterate through all nodes. If input values
             * are available on that node, push output and repeat.
             * This will probably end up with the input going first, because
             * it is likely to be parsed into a lower nodeId, which is desirable
             * in terms of aesthetics.
             */
             
            // graph information
            int numNodes = topology->getNumNodes();
            int numEdges = topology->getNumEdges();
            // keep track of schedule, padd for multiple executions
            int testSchedule[MAX_SCHED_LEN];
            int scheduledNodes = 0;
            // storage pointer for iteration 
            Node* tempNode;
            int* tempIn;
            int* tempOut;
            int pushable;
            while(true){
                for(int node=0; node<numNodes; ++node){
                    tempNode = topology->getNode(node);
                    if(tempNode->IsInputAvailable()){
                        if(tempNode->get_node_id() == 'O'){
                            // this is the output node, i.e. we have completed a cycle.
                            // break out of the loop and store test schedule as final schedule.
                            for(int i=0; i< MAX_SCHED_LEN; i++){
                                _schedule[i] = testSchedule[i];
                            return true;
                        }
                        // inputs are available, but can we push them? If this is an upsampler, can
                        // we push `n' data points?
                        pushable = topology->numPushable(node);
                        if(tempNode->get_node_id() == 'U'){
                            if(pushable < tempNode->getNumSamples))
                                continue;
                        }else{
                            if(pushable == 0){
                                continue;
                            }
                        }
                        // inputs available on this node and we can push the output. process these inputs,
                        // push them to output, and "pull" outputs from our input(s) 
                        tempNode->ProcessInputs();
                        tempIn = tempNode->getInEdges();
                        tempOut = tempNode->getOutEdges();
                        // pull outputs from incoming nodes
                        for(int i=0; i<4; i++){
                            int inEdge = tempIn[i];
                            if(inNode != -1)
                                topology->getNode(inNode)->PullOutput();
                        }
                        // push outputs to outgoing nodes
                        for(int i=0; i<4; i++){
                            int outEdge = tempOut[i];
                            if(outNode != -1)
                                topology->getNode(outNode)->PushInput(0);
                        }
                        // we just executed this node, put it to the test schedule
                        testSchedule[scheduledNodes++] = node;
                        // do not check the rest of the nodes, because we just pushed an output.
                        continue;
                    }
                }
                // if we ever get this far, then we checked all nodes and no node is ready to
                // be processed. In other words, this is not schedulable.
                return false;
            }  
            
        }
        
        
        void PrintSchedule(Graph* topology) {
            string scheduleToPrint;
            for(int i=0; i<MAX_SCHED_LEN; i++){
                if(_schedule[i] != 0){
                    int thisNode = _schedule[i];
                    pc.printf("%s", topology->getNode(thisNode)->get_node_id());
                    pc.printf("%d", thisNode);
                    pc.printf(" ");
                }
            }
        }
         
    private:
        
};

#endif
