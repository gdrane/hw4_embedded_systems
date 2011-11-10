#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include "Edge.h"
#include "Node.h"

using namespace std;

class Graph {
    public:
        Graph(int noofnodes, int noofedges) {
            _noofnodes = noofnodes;
            _noofedges = noofedges;
            *_adjacency_matrix = new int[noofnodes];
            for(int i = 0; i < noofnodes; ++i) {
                _adjacency_matrix[i] = new int[noofnodes];
            }
            *_edge_matrix = new vector<Edge*> [noofnodes];
            for(int i = 0; i < noofnodes; ++i)
                _edge_matrix[i] = new vector<Edge*>();
        }
        
        ~Graph() {
             for(int i = 0; i < _noofnodes; ++i)
                delete[] _adjacency_matrix[i];
             delete[] _adjacency_matrix;
             for(int i = 0;i < _noofnodes; ++i)
                delete[] _edge_matrix[i];
             delete[] _edge_matrix;
             map<int, Node*>::iterator map_it;
             for(map_it = _node_map.begin(); map_it != _node_map.end(); ++map_it)
                delete map_it->second;
         }         
                  
        void EnterAdjacency(int fromnode, int tonode) {
            if(_node_map.find(fromnode) == _node_map.end() || _node_map.find(tonode) == _node_map.end()) {
                printf("Please enter all the nodes in the graph before describing adjacency between them\n");
                return;
            }
            _adjacency_matrix[fromnode][tonode] = 1;
        }
        
        void EnterEdge(Edge* edge) {
            if(edge == NULL)    
                return;
            // To assert that same edge is not entered twice we can maintain edge_matrix as a map
            _edge_matrix[edge->from_node()][edge->to_node()].push_back(edge);
        	EnterAdjacency(edge->from_node(), edge->to_node());
		}
        
        void EnterNode(Node* node) {
            if(node == NULL || _node_map.find(node->get_node_no()) != _node_map.end()) {
                printf("ERROR: SDFG FORMAT ERROR\n");
                return;
            }
            _node_map.insert(pair<int, Node*>(node->get_node_no(), node));
        }
        
    private:
        map<int, Node*> _node_map;
        int **_adjacency_matrix;
        vector<Edge*> **_edge_matrix;
        int _noofnodes;
        int _noofedges;
};
#endif 
