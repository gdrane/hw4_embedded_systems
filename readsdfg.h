#ifndef READSDFG_H
#define READSDFG_H

// -- file includes --
#include <fstream>
#include <string>   
#include <vector>
#include "mbed.h"
#include "Graph.h"
#include "Node.h"

// -- defines --
#define INPUT_SIZE 20

// -- variables --

struct edge_info{
    int edgeno,from,to;
};
int edge_count = 0;
map<int,struct edge_info> edges;

// -- function headers --
void PrintSdfgFormatError();
Graph* ReadScheduleConfig();

// -- function implementations -
void PrintSdfgFormatError(){
    error("ERROR: BAD SDFG FORMAT\r\n");
}

Graph* ReadScheduleConfig() {
    Graph* input_graph;
    // does the file exist?
    FILE *file = fopen("/local/sdfgconf.txt", "r");
    if (!(file)){
        error("ERROR: NO SDFG");
    }else{
        fclose(file);
    }
    ifstream sdfginput("/local/sdfgconf.txt");
    // is the file empty?
    if(sdfginput.eof()) {
        PrintSdfgFormatError();
        return NULL;
    }
    int noofnodes, noofedges;
    char str[INPUT_SIZE];
    int input_size = INPUT_SIZE;
    sdfginput.getline(str, input_size);
    char *token = strtok(str, " ");
    if(token == NULL) {
        PrintSdfgFormatError();
        return NULL;
    }
    noofnodes = atoi(token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        PrintSdfgFormatError();
        return NULL;
    }
    noofedges = atoi(token);
    token = strtok(NULL, " ");
    if(token != NULL) {
        PrintSdfgFormatError();
        return NULL;
    }
    pc.printf("Nodes: %d, Edges: %d\n\r", noofnodes, noofedges);
    input_graph = new Graph(noofnodes, noofedges);
    pc.printf("Nodes: %d, Edges: %d\n\r", noofnodes, noofedges);
    while(!sdfginput.eof()) {
        char node_type = '\0';
        int tokeniter = 0;
        Node *newnode;
        sdfginput.getline(str, input_size);
        pc.printf("str: %s\n\r",str);
        char *token = strtok(str, " ");
        do {
            pc.printf("Token: %s\n\r",token);
            if (token == NULL) {
                PrintSdfgFormatError();
                return NULL;
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
                            break;
                    case 'D' :
							token = strtok(NULL, " ");
							if(token == NULL) {
								PrintSdfgFormatError();
								return;
							}
							++tokeniter;
							int dwnsample = atoi(token);
                            newnode = new DNode(dwnsample);
                            break;
                    case 'U' :
							token = strtok(NULL , " ");
							if(token == NULL) {
								PrintSdfgFormatError();
								return;
							}
							++tokeniter;
							int upsample = atoi(token);
                            newnode = new UNode(upsample);
                            break;
                    case 'M' :
							token = strtok(NULL, " ");
							if(token == NULL) {
								PrintSdfgFormatError();
								return;
							}
							++tokeniter;
							int multconst = atoi(token);
							token = strtok(NULL, " ");
							if(token == NULL) {
								PrintSdfgFormatError();
								return;
							}
							++tokeniter;
							int divconst = atoi(token);
                            newnode = new MNode(multconst, divconst);
                            break;
                    case 'F' :
                            newnode = new FNode();
                            break;
                    case 'C' :
                            newnode = new CNode();
                            break;
					case 'E' :
							token = strtok(NULL, " ");
							if(token == NULL) {
								PrintSdfgFormatError();
								return;
							}
							int edgeno = atoi(token);
							token = strtok(NULL, " ");
							if(token == NULL) {
								PrintSdfgFormatError();
								return;
							}
							int buffer_size = atoi(token);
							token = strtok(NULL, " ");
							if(token == NULL) {
								PrintSdfgFormatError();
								return;
							}
							int initial_sample = atoi(token);
							token = strtok(NULL, " ");
							int old_sample; 
							if(token != NULL) {
								old_sample = atoi(token);
							}	
							newnode = new DelayNode(edgeno, buffer_size, initial_sample, old_sample);
							break;
                    default:
                            PrintSdfgFormatError();
                            return NULL;
                }
                // Adding to node to graph map
                input_graph->EnterNode(newnode);
            }
            // For the Edge information
            if(tokeniter > 0) {
                struct edge_info temp;
                int edgeno = atoi(token);
                switch(node_type) {
                     case 'I' :
                            // I oe1 [oe2 , oe3 ...]
							newnode->AddEgdeOut(edgeno);
                     		input_graph->EnterOutEdge(newnode->get_node_no(), edgeno);
                            break;
                    case 'O' :
                            if (tokeniter > 1) {
                                PrintSdfgFormatError();
                                return NULL;
                            }
							newnode->AddInEdge(edgeno);
                            input_graph->EnterInEdge(newnode->get_node_no(), edgeno);
                            break;
                    case 'A' :
                            // A ie1 ie2 oe1 [oe2 oe3...]
                            if(tokeniter == 1 || tokeniter == 2) {
								newnode->AddInEdge(edgeno);
								input_graph->EnterInEdge(newnode->get_node_no(), edgeno);
                            } else {
								newnode->AddOutEdge(edgeno);
								input_graph->EnterOutEdge(newnode->get_node_no(), edgeno);
                            }
                            break;
                    case 'S' :
                             // S ie1 ie2 oe1 [oe2 oe3 ...]
                            if( tokeniter == 1 || tokeniter == 2) {
								newnode->AddInEdge(edgeno);
                                input_graph->EnterInEdge(newnode->get_node_no(), edgeno);
                            } else {
								newnode->AddOutEdge(edgeno);
                                input_graph->EnterOutEdge(newnode->get_node_no(), edgeno);
                            }
                            break;
                    case 'M' :
                            // M c d ie oe1[oe2 oe3...]
                            if( tokeniter == 3) {
                                newnode->AddInEdge(edgeno);
								input_graph->EnterInEdge(newnode->get_node_no(), edgeno);
                            } else if (tokeniter > 3){
								newnode->AddOutEdge(edgeno);
                                input_graph->EnterOutnewnode->get_node_no();
                            }
                            break;
                    case 'D' :
                            // D n ie oe1[ oe2...]
                            if (tokeniter == 2) {
								newnode->AddInEdge(edgeno);
								input_graph->EnterInEdge(newnode->get_node_no(), edgeno);
                            } else if (tokeniter > 2) {
								newnode->AddOutEdge(edgeno);
								input_graph->EnterOutEdge(newnode->get_node_no, edgeno);
                            }
                            break;
                    case 'U' :
                            // U n ie oe1 [oe2 oe3...]
                            if (tokeniter == 2) {
								newnode->AddInEdge(edgeno);
                                input_graph->EnterInEdge(newnode->get_node_no(), edgeno);
                            } else if(tokeniter > 2) {
								newnode->AddOutEdge(edgeno);
                                input_graph->EnterOutEdge(newnode->get_node_no(), edgeno);
                            }
                            break;
                    case 'F' :
                            // F ie oe1 oe2[oe3, oe3...]
                            if (tokeniter == 1) {
								newnode->AddInEdge(edgeno);
                                input_graph->EnterInEdge(newnode->get_node_no(), edgeno);
                            } else {
								newnode->AddOutEdge(edgeno);
                                input_graph->EnterOutEdge(newnode->get_node_no(), edgeno);
                            }
                            break;
                    case 'C' :
                            // C k
                            if (tokeniter > 1) {
                                PrintSdfgFormatError();
                                return NULL;
                            }
                            break;
                    default: break;

                }
                // TODO(gdrane): Have to add error handling for input underflow
            }
            // Incrementing no of tokens parsed
            ++tokeniter;
        } while((token = strtok(NULL, " ")) != NULL);
    }
    sdfginput.close();
    return(&input_graph);
}

#endif
