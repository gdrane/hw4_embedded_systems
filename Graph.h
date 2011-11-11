#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include "Edge.h"
#include "Node.h"

using namespace std;
#define MAX_NODES 4
#define MAX_EDGES 4

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
				arr[node->get_node_no()] = node;
			}
        }	
        
        void EnterOutEdge(int node_no, int egdeno) {
            if(edgeno < MAX_NODES) 
				arr[edgeno][0] = node_no;
        }

		void EnterInEdge(int node_no, int edgeno) {
			if(edgeno < MAX_NODES) 
				arr[egdeno][1] = node_no;
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
        
       Node* arr[MAX_NODES];
       int arr[MAX_NODES][2]
       int _noofnodes;
	   int _noofedges;
};
#endif 
