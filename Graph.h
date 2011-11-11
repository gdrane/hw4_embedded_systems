#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include "Edge.h"
#include "Node.h"

using namespace std;
#define MAX_NODES 30
#define MAX_EDGES 30


class Graph {
    public:
        Graph(int noofnodes, int noofedges) {
            pc.printf("graph constructor\n\r");
            _noofnodes = noofnodes;
            _noofedges = noofedges;
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
        
        int getNumEdges(){
            return _noofedges;
        }
        
        int getNumNodes(){
            return _noofnodes;
        }

        Node* getNode(int key){
           // return _node_map[key];
        }
        
       Node* nodes[MAX_NODES];
       int edgeinfo[MAX_NODES][2];
       int _noofnodes;
       int _noofedges;
};
#endif 
