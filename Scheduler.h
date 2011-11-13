#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include "Graph.h"
#include "Node.h"

#define MAX_SCHED_LEN 128

using namespace std;
class Scheduler{
    public:
        Scheduler(Graph* inputGraph){
            topology = inputGraph;
            _schedLen = 0;
        }
        
        bool isSchedulable(){
            /* Iterate through all nodes. If input values
             * are available on all inputedges, push output and repeat.
             * This will probably end up with the input going first, because
             * it is likely to be parsed into a lower nodeId, which is desirable
             * in terms of aesthetics.
             */
             
            // graph information
            int numNodes = topology->getNumNodes();
            int numEdges = topology->getNumEdges();
            
            // keep track of schedule, pad for multiple executions
            int testSchedule[MAX_SCHED_LEN];
            int scheduledNodes = 0;
            
            // flags for finished schedule
            bool outputReached = false;
            int initialNode = -1;
            
            // iteration variables
            int nodeToSchedule = -1;
            bool canGo[numNodes];
            bool oneCanGo = false;
            int numRuns[numNodes];
            for(int i=0; i<numNodes; i++){
                canGo[i] = false;
                numRuns[i] = 0;
            }
            int minRuns = 0;
            
            // scheduling loop
            while(1){
                // get a list of those that can run
                oneCanGo = false;
                for(int i=0; i<numNodes; i++){
                    if(isReadyToSchedule(i)){
                        canGo[i] = true;
                        oneCanGo = true;
                    }
                }
                if(!oneCanGo)
                    // no node can go
                    return false;
                    
                // schedule the one that has gone the least
                minRuns = 1000;
                for(int i=0; i<numNodes; i++){
                    if(canGo[i] && numRuns[i] < minRuns){
                        minRuns = numRuns[i];
                    }
                }
                for(int i=0; i<numNodes; i++){
                    if(canGo[i] && numRuns[i] == minRuns){
                        // schedule it
                        nodeToSchedule = i;
                        numRuns[i] = numRuns[i]+1;
                        break;
                    }
                }

                // inputs available on this node and we can push the output. process these inputs
                
                topology->processNode(nodeToSchedule);
                if(initialNode == -1){
                    initialNode = nodeToSchedule;
                }
                if(topology->getNode(nodeToSchedule)->get_node_id() == 'O')
                    outputReached = true;
                    
                // check to see if our schedule is complete
                if(initialNode == nodeToSchedule && outputReached){
                    for(int i=0; i<scheduledNodes; i++){
                        _schedule[i] = testSchedule[i];
                    }
                    _schedLen = scheduledNodes;
                    return true;
                }
                
                // we just executed this node, put it to the test schedule
                testSchedule[scheduledNodes++] = nodeToSchedule;
                 
            }
        }
      
        bool isReadyToSchedule(int node){
            Node* thisNode = topology->getNode(node);
            int numInputs = topology->numInputsAvailable(thisNode->get_node_no(), true);
            int numPushable = topology->numPushable(thisNode->get_node_no(), true);
            
            if(numInputs > 0 && numPushable > 0){
                               
                // if this is a downsampler, are enough inputs available?
                if(thisNode->get_node_id() == 'D'){
                    if(numInputs < ((DNode*)thisNode)->getN())
                        return false;
                }
                // if this is an upsampler, is there enough pushable?
                if(thisNode->get_node_id() == 'U'){
                    if(numPushable < ((UNode*)thisNode)->getN())
                        return false;
                }
                
                // otherwise this node is ready to be scheduled
                return true;
            }else{
                return false;
            }
            
        }
        
        int getScheduleLength(){
            return _schedLen;
        }
        int* getSchedule(){
            return _schedule;
        }
        void PrintSchedule(){
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
        // variables
        Graph* topology;
        int _schedule[MAX_SCHED_LEN];
        int _schedLen;
};

#endif
