#ifndef NODE_H
#define NODE_H

#include "Graph.h"
#define MAX_BUFF_LEN 10

// Node Template -- to be inherited
class Node {
    public:
        // constructor
        Node () {
            _nodeno = NodeNoCount++;
        }
        // inherited functions
        virtual int ProcessInputs(int* inputs){ return 0; }
        virtual char get_node_id(){return 'X';}
        // superclass functions
        int get_node_no() { return _nodeno;}

    protected:
        int _nodeno;
        static int NodeNoCount;        
};

int Node::NodeNoCount;


// Input Node Class
class INode : public Node {
    public:
        INode(){ 
        }
        virtual int ProcessInputs(int* in) {
            return in[0];
        }
        virtual char get_node_id(){return 'I';}

};

// Output Node Class
class ONode : public Node {
    public:
        ONode(){
        }
        virtual int ProcessInputs(int* in) {
            return in[0];
        }
        virtual char get_node_id(){return 'O';}
};

// Addition Node Class
class ANode : public Node {
    public:
        ANode(){
        }
        virtual int ProcessInputs(int* in) {
            return in[0] + in[1];
        }   
        virtual char get_node_id(){return 'A';}  
};

// Subtraction Node Class
class SNode : public Node {
    public:
        SNode(){
        }
        virtual int ProcessInputs(int* in) {
            return in[0]-in[1];
        }      
        virtual char get_node_id(){return 'S';}  
};

// Multiplication Node Class
class MNode : public Node {
    public :
        MNode(int _multconst, int _divconst) {
            multconst = _multconst;
            divconst = _divconst;
        }
        virtual int ProcessInputs(int* in) {
            return in[0]*multconst / divconst;   
        }
        virtual char get_node_id(){return 'M';}

    private:
        int multconst, divconst;
};    

// Downsample Node Class
class DNode : public Node {
    public:
        DNode(int _nsample) {
            _downsample = _nsample;
        }
        virtual int ProcessInputs(int* in) {
            return in[0];
        }
        virtual char get_node_id(){return 'D';}
        // Buffer functions
        int getN() {
            return _downsample;
        }
        
    private :
        int _downsample;
};

// Upsample Node Class
class UNode : public Node {
    public:
        UNode(int _nsample) {
            _upsample = _nsample;
        }
        /* This isn't exactly right. we need to output multiple */
        virtual int ProcessInputs(int* in) {
            return in[0];
        }
        virtual char get_node_id(){return 'U';}

        int getN() {
            return _upsample;
        }
        
    private :
        int _upsample;
};

// Fork Node Class
class FNode : public ONode {
       public:
            FNode(){
            }
            virtual int ProcessInputs(int* in) {
                return in[0];
            }
            virtual char get_node_id(){return 'F';}
};

// Constant Node Class
class CNode : public Node {
    public:
        CNode(int val){
            _val = val;
        }
        virtual int ProcessInputs(int* in) {
            return _val;
        }
        virtual char get_node_id(){return 'C';}
    private:
        int _val;
};

#endif
