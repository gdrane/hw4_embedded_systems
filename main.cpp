#include <vector>
#include <fstream>

#include "mbed.h"

#include "Graph.h"
#include "GraphTraveller.h"
#include "Node.h"
#include "Processor.h"
#include "Scheduler.h"

#define INPUT_SIZE 50

Graph* input_graph;
struct edge_info{
	int edgeno,from, to;
};
int edge_count = 0;
map<int,struct edge_info> edges;

void PrintSdfgFormatError() {
    printf("ERROR: BAD SDFG FORMAT\n");
}

void ReadScheduleConfig() {
    FILE *fp = fopen("/local/sdfgconf.txt", "r");
    if(fp == NULL) {
        printf("ERROR: NO SDFG\n");
    }
    int noofnodes, noofedges;
    if(!feof(fp) && fscanf(fp, "%d %d" , &noofnodes, &noofedges) != 2) {
        PrintSdfgFormatError();
		return;
    }
	input_graph = new Graph(noofnodes, noofedges);
	char* str = (char*) malloc( sizeof(char) * INPUT_SIZE);
	while(feof(fp)) {
		int bytes_read = 0;
		char node_type = '\0';
		int tokeniter = 0;
		Node *newnode;
		bytes_read = getline(str, &input_size, fp);
		char *token = strtok(str, " ");
		do {
			if (token == NULL ||  strlen(token) > 1) {
				PrintSdfgFormatError();
				return;
			}
			if (node_type == '\0') {
				node_type = token[tokeniter];
				switch(node_type) {
					case 'I' :
							newnode = new INode();
							break;
					case 'O' :
							newnode = new ONode();
							break;
					case 'A' : 
							newnode = new ANode();
							break;
					case 'S' :
							newnode = new SNode();
							break
					case 'D' :
							newnode = new DNode();
							break;
					case 'U' :
							newnode = new UNode();
							break;
					case 'M' :
							newnode = new MNode();
							break;
					case 'F' :
							newnode = new FNode();
							break
					case 'C' :
							newnode = new CNode();
							break;
					default:
							PrintSdfgFormatError();
							return;
							break;
				}
				// Adding to node to graph map
				input_graph->EnterNode(newnode);
			}
			// For the Edge information
			if(tokeniter > 0) {
				Edge* edge;
				map<int, struct edge_info>::iterator map_it;
				struct edge_info temp
				int edgeno = atoi(token);
				if((map_it = edges.find(edgeno)) != edges.end()) {
					temp = map_it->second;		
				} else {
					temp.edgeno = edgeno;
				}
				switch(node_type) {
			 		case 'I' :
						    // I oe1 [oe2 , oe3 ...]
							temp.from = newnode->get_node_no();
							break;
					case 'O' :
							if (tokeniter > 1) {
								PrintSdfgFormatError();
								return;
							}
							temp.to = newnode->get_node_no();
							break;
					case 'A' :
							// A ie1 ie2 oe1 [oe2 oe3...]
							if(tokeniter == 1 || tokeniter == 2) {
								temp.to = newnode->get_node_no();
							} else {
								temp.from = newnode->get_node_no();
							}	
							break;
					case 'S' :
					 		// S ie1 ie2 oe1 [oe2 oe3 ...]
							if( tokeniter == 1 || tokeniter == 2) {
								temp.to = newnode->get_node_no();
							} else {
								temp.from = newnode->get_node_no();
							}
							break;
					case 'M' :
							// M c d ie oe1[oe2 oe3...]
							if( tokeniter == 3) {
								temp.to = newnode->get_node_no();
							} else if (tokeniter > 3){
								temp.from = newnode->get_node_no();
							}
							break;
					case 'D' :
							// D n ie oe1[ oe2...]
							if (tokeniter == 2) {
								temp.to = newnode->get_node_no();
							} else if (tokeniter > 2) {
							 	temp.from = newnode->get_node_no();
							}
							break;
					case 'U' :
							// U n ie oe1 [oe2 oe3...]
							if (tokeniter == 2) {
								temp.to = newnode->get_node_no();
							} else if(tokeniter > 2) {
								temp.from = newnode->get_node_no();
							}
							break;
					case 'F' :
							// F ie oe1 oe2[oe3, oe3...]
							if (tokeniter == 1) {
								temp.to = newnode->get_node_no();
							} else {
							 	temp.from = newnode->get_node_no();
							}
							break;
					case 'C' :
							// C k
							if (tokeniter > 1) {
								PrintSdfgFormatError();
								return;
							}
							break;
					default: break

				}
				// insert the temp struct back to the map
				edges.insert(pair<int, struct edge_info>(edgeno, temp));
			}
			// Incrementing no of tokens parsed
			++tokeniter;
		} while((token = strtok(NULL, " ")) != NULL);
	}
	map<int, struct edge_info>::iterator edge_map_it;
	for(edge_map_it = edges.begin(); edge_map_it != edges.end(); ++edge_map_it) {
		Egde* newedge = new Edge(edge_map_it->second.from,
								edge_map_it->second.to);
		input_graph->EnterEdge(newedge);	
	}
    fclose(fp);
}

// -- Variables --
DigitalOut pin21(p21);
DigitalOut pin22(p22);
DigitalOut pin23(p23);

// -- Function Implementations --
void set(char pin){
    switch(pin){
        case 21:
            pin21 = 1;
            break;
        case 22:
            pin22 = 1;
            break;
        case 23:
            pin23 = 1;
            break;
        default:
            break;
    }
}
void clear(char pin){
    switch(pin){
        case 21:
            pin21 = 0;
            break;
        case 22:
            pin22 = 0;
            break;
        case 23:
            pin23 = 0;
            break;
        default:
            break;
    }
}


int main() {
    // Initializing pins 21, 22, 23 to zero
    pin21 = pin22 = pin23 = 0;
    while(1) {
    wait(0.2);
    }
    return 0;
}

