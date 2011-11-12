#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

using namespace std;
#define MAX_NODES 30
#define MAX_DELAY 10

class Graph {
    public:
        Graph(int noofnodes, int noofedges) {
            _noofnodes = noofnodes;
            _noofedges = noofedges;
            // clear out memory used for our arrays (not necessary?)
            for(int i=0; i<MAX_NODES; i++){
                edgeinfo[i][0] = 0;
                edgeinfo[i][1] = 0;
                delayinfo[i][0] = 0;
            }
        }
        
        ~Graph() {
        }         
                  
        void EnterNode(Node* node) {
            if(node->get_node_no() < MAX_NODES) {
                nodes[node->get_node_no()] = node;
            }
        }    
        
        void EnterOutEdge(int node_no, int edgeno) {
            if(edgeno < MAX_NODES) 
                edgeinfo[edgeno][0] = node_no;
        }

        void EnterInEdge(int node_no, int edgeno) {
            if(edgeno < MAX_NODES) 
                edgeinfo[edgeno][1] = node_no;
        }
        
        void EnterDelay(int edgeno, int delayCount, int* ic){
            if(edgeno < MAX_NODES){
                delayinfo[edgeno][0] = delayCount;
                delayinfo[edgeno][1] = 0; // num queued
                for(int i=0; i<delayCount; i++){
                    delayinfo[edgeno][1+i] = ic[i];
                }
            }
        }
        
        int getNumEdges(){
            return _noofedges;
        }
        
        int getNumNodes(){
            return _noofnodes;
        }

        Node* getNode(int key){
           return nodes[key];
        }
        int pullOneInput(int nodeno, int edgeno){
            Node* thisNode = nodes[nodeno];
            Node* inNode;
            if(delayinfo[edgeno][0] > 0){
                // buffer on this edge 
                if(delayinfo[nodeno][1] == delayinfo[nodeno][0]){
                    return 0;
                }else{
                    // underfull buffer -> can push
                    tempPushable =  delayinfo[nodeno][0] - delayinfo[nodeno][1];
                    if(tempPushable < minPushable)
                        minPushable = tempPushable;
                    }
            }else{
                // no buffer on this edge
                outNode = nodes[edgeinfo[thisEdge][1]];
                if(outNode->IsInputAvailable())
                    return 0;
                // no buffer, inputs not there yet -> can push
                minPushable = 1;
            }
        }
        
        void PushOneOutput(int nodeno){
        }
        
        int numPushable(int nodeno){
            // loop through all output nodes to see if they
            // can accept an input, or if the output edge has
            // an underfull buffer
            Node* thisNode = nodes[nodeno];
            Node* outNode;
            int numOut = thisNode->getNumOutputs();
            int thisEdge = 0;
            int minPushable, tempPushable = 0;
            for(int i=0; i<numOut; i++){
                thisEdge = thisNode->getOutEdge(i);
                // buffer on this edge
                if(delayinfo[thisEdge][0] > 0){
                    // full buffer -> can't push   
                    if(delayinfo[thisEdge][1] == delayinfo[thisEdge][0]){
                        return 0;
                    }else{
                        // underfull buffer -> can push
                        tempPushable =  delayinfo[thisEdge][0] - delayinfo[thisEdge][1];
                        if(tempPushable < minPushable)
                            minPushable = tempPushable;
                        }
                }else{
                    // no buffer, inputs already there -> can't push
                    outNode = nodes[edgeinfo[thisEdge][1]];
                    if(outNode->IsInputAvailable())
                        return 0;
                    // no buffer, inputs not there yet -> can push
                    minPushable = 1;
                }
            }
            return minPushable;
        }
        
        
        void Print(){
            pc.printf("\n\r------ Graph Topology ---------\n\r");
            pc.printf(" %d Nodes and %d Edges\n\r",_noofnodes,_noofedges);
            pc.printf("Nodes: \n\r");
            for(int i=0; i<_noofnodes; i++){
                pc.printf("%c%d ",nodes[i]->get_node_id(),nodes[i]->get_node_no());
            }
            pc.printf("\n\rEdges: \n\r");
            for(int i=1; i<=_noofedges; i++){
                pc.printf("(%d,%d) ",edgeinfo[i][0],edgeinfo[i][1]);
            }
            pc.printf("\n\rDelays: \n\r");
            for(int i=2; i<_noofedges+2; i++){
                if(delayinfo[i][0] > 0)
                    pc.printf("(%d @ %d) ", delayinfo[i][0], i);
            }
        }
        
       Node* nodes[MAX_NODES];
       int edgeinfo[MAX_NODES][2];
       int delayinfo[MAX_NODES][MAX_DELAY+2];
       int _noofnodes;
       int _noofedges;
};
#endif 
