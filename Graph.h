#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include "Edge.h"

using namespace std;
#define MAX_NODES 30
#define MAX_DELAY 10

class Graph {
    public:
        // Constructor & Destructor
        Graph(int noofnodes, int noofedges) {
            _noofnodes = noofnodes;
            _noofedges = noofedges;
            // make all edges
            for(int i=1; i<=noofedges; i++){
                edges[i] = new Edge(i);
            }
        }
        
        ~Graph() {
        }         
                  
        void EnterNode(Node* node) {
            if(node->get_node_no() < MAX_NODES) {
                nodes[node->get_node_no()] = node;
            }
        }    
        
        void EnterOutEdge(int nodeno, int edgeno) {
            // add the output to this edge
            edges[edgeno]->enterOutput(nodeno);
        }

        void EnterInEdge(int nodeno, int edgeno) {
            // add the output to this edge
            edges[edgeno]->enterInput(nodeno);
        }
        
        void EnterDelay(int edgeno, int delayCount, int* ic){
            edges[edgeno]->enterDelay(delayCount);
            for(int i=0; i<delayCount; i++){
                edges[edgeno]->push(ic[i]);
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
        
        Edge* getEdge(int key){
            return edges[key];
        }
        int getInputNode(){
            for(int i=0; i<_noofnodes; i++){
                if(nodes[i]->get_node_id() == 'I')
                    return i;
            }
            return -1;
        }
        int getOutputNode(){
            for(int i=0; i<_noofnodes; i++){
                if(nodes[i]->get_node_id() == 'O')
                    return i;
            }
            return -1;
        }
        
        int numInputsAvailable(int nodeno, bool scheduling){
            /* check the minimum number of inputs available
             * on any given input edge of this node
             */
             
             // if we're scheduling, Input node always has inputs
             if(scheduling && getNode(nodeno)->get_node_id() == 'I'){
                return 1000;
            }
            
            // constant nodes always have inputs
            if(getNode(nodeno)->get_node_id() == 'C'){
                return 1000;
            }
                      
            int minAvailable = 1000;
            int tempAvailable = 1000;
            // find the input edges to this node
            for(int i=1; i<=_noofedges; i++){
                if(edges[i]->getOutput() == nodeno){
                    // this edge points to this node
                    tempAvailable = edges[i]->numPoppable();
                    if(tempAvailable < minAvailable){
                        minAvailable = tempAvailable;
                    }
                }
            }
            return minAvailable;
        }
        
        void processNode(int nodeno){
            Node* thisNode = nodes[nodeno];
            // get inputs, accounting for downsamples
            int inputVals[MAX_DELAY];
            int index = 0;
            
            int N = 1;
            if(thisNode->get_node_id() == 'D')
                N = ((DNode*)thisNode)->getN();
            for(int n=0; n<N; n++){
                for(int e=1; e<=_noofedges; e++){
                    if(edges[e]->getOutput() == nodeno){
                        inputVals[index++] = edges[e]->pop();
                    }
                }
            }
            // process and push outputs, accounting for upsamples
            int outVal = thisNode->ProcessInputs(inputVals);
            N = 1;
            if(thisNode->get_node_id() == 'U')
                N = ((UNode*)thisNode)->getN();
            for(int n=0; n<N; n++){
                for(int e=1; e<=_noofedges; e++){
                    if(edges[e]->getInput() == nodeno){
                        edges[e]->push(outVal);
                    }
                }
            }
        }
        
        int numPushable(int nodeno, bool scheduling){
            // loop through all output edges to see if they
            // can accept an input
            
            // output node can always be pushed
            if(getNode(nodeno)->get_node_id() == 'O'){
                return 1000;
            }
                        
            int minPushable = 1000;
            int tempPushable = 1000;
            
            // find the out edges of this node
            for(int i=1; i<=_noofedges; i++){
                if(edges[i]->getInput() == nodeno){
                    tempPushable = edges[i]->numPushable();
                    if(tempPushable < minPushable){
                        minPushable = tempPushable;
                    }
                }
            }
            return minPushable;
        }
        
        
        void Print(){
            pc.printf("\n\r------ Graph Topology ---------\n\r");
            pc.printf(" %d Nodes and %d Edges\n\r",_noofnodes,_noofedges);
            pc.printf("Nodes: \n\r");
            pc.printf("------------------\n\r");
            for(int i=0; i<_noofnodes; i++){
                pc.printf("%c%d\n\r",nodes[i]->get_node_id(),nodes[i]->get_node_no());
            }
            pc.printf("\n\rEdges: \n\r");
            pc.printf("------------------\n\r");
            for(int i=1; i<=_noofedges; i++){
                pc.printf("%d: (%d,%d)\n\r",i,edges[i]->getInput(), edges[i]->getOutput());
            }
            pc.printf("\n\rDelays: \n\r");
            pc.printf("------------------\n\r");
            for(int i=1; i<=_noofedges; i++){
                if(edges[i]->hasDelay())
                    pc.printf("(%d @ %d)\n\r", edges[i]->numPoppable(), edges[i]->getId());
            }
            pc.printf("\n\rBuffers: \n\r");
            pc.printf("------------------\n\r");
            for(int i=1; i<=_noofedges; i++){
                pc.printf("%d: %d\n\r", i,edges[i]->bufferSize());
            }
            pc.printf("\n\r");
            
        }
        
   private:
       Node* nodes[MAX_NODES];
       Edge* edges[MAX_NODES];
       int _noofnodes;
       int _noofedges;
};
#endif 
