#ifndef NODE_H
#define NODE_H

#include "Graph.h"

// Node Template -- to be inherited
class Node {
    public:
        void ProcessInputs();
        bool IsOutputAvailable();
        bool PushInput(int val, int index);
        int PullOutput();
        virtual char get_node_id(){return 'X';}
        Node () {
            _nodeno = NodeNoCount++;
            // no inputs or outputs by default
            edge_in[0] = edge_in[1] = edge_in[2] = edge_in[3] = -1;
            edge_out[0] = edge_out[1] = edge_out[2] = edge_out[3] = -1;
        }
        int get_node_no() { return _nodeno;}
        void AddInEdge(int edgeno) {
            if(edge_in_count < 4)
                edge_in[edge_in_count++] = edgeno;
        }
        void AddOutEdge(int edgeno) {
            if(edge_out_count < 4)
                edge_out[edge_out_count++] = edgeno;
        }
        int getInEdge(int index){
            return edge_in[index];
        }
        int getOutEdge(int index){
            return edge_out[index];
        }
        int getNumOutputs(){
            return edge_out_count;
        }

    private:
        int _nodeno;
        int edge_in[4];
        int edge_out[4];
        static int edge_in_count;
        static int edge_out_count;
        static int NodeNoCount;        
};

int Node::NodeNoCount;
int Node::edge_in_count;
int Node::edge_out_count;

/*
class DelayNode : public Node {
    public:
        int edge_no() { return edgeno;}
        int buffer_size() { return buffersize; }
        int old_sample() { return oldsample; }
        int initial_sample() { return initialsample; }
        DelayNode(int _edgeno, int _buffer_size, int _initial_sample, int _old_sample=0) {
              edgeno = _edgeno;
            buffersize = _buffer_size;
            initialsample = _initial_sample;
            oldsample = _old_sample;
        }
        virtual char get_node_id(){ return 'D'; }

    private:
        int buffersize;
        int initialsample;
        int oldsample;
        int edgeno;
};
*/

// Input Node Class
class INode : public Node {
    public:
        bool IsInputAvailable(){
            return inavail;
          }

        bool IsOutputAvailable() {
               return outavail;
        }

        bool PushInput(int val) {
            if(!inavail) {
                input = val;
                inavail = true;
                return true;
            }else{
                return false;
            }
        }

        int PullOutput() {
            if(outavail) {
                outavail = false;
                return output;
            }
            return 0;
        }

        void ProcessInputs() {
            if(inavail) {
                output = input;
                inavail = false;
                outavail = true;
            }
        }
    virtual char get_node_id(){return 'I';}
    private:
        bool inavail;
        bool outavail;
        int input;
        int output;
};

// Output Node Class
class ONode : public Node {
    public:
        bool IsInputAvailable() {
            return inavail;
        }

        bool IsOutputAvailable() {
            return outavail;
        }

        bool PushInput(int val) {
           if(!inavail) {
                input = val;
                inavail = true;
                return true;
            }else{
                return false;
            }
        }

        int PullOutput() {
            if(outavail) {
                outavail = false;
                return output;
            }
            return -1;
        }

        void ProcessInputs() {
            if(inavail) {
                output = input; 
                inavail = true;
                outavail = false;
            }
        }
    virtual char get_node_id(){return 'O';}
    private:
        bool inavail, outavail;
        int input, output;
};

// Addition Node Class
class ANode : public Node {
    public:
        bool IsInputAvailable() {
            if(inavail[0] == inavail[1] == true)
               return true;
            return false;
        }
        
        bool IsOutputAvailable() {
            return outavail;
        }
        
        bool PushInput(int val) {
            if(!inavail[0]) {
                inputs[0] = val;
                inavail[0] = true;
                return true;
            }
            if (!inavail[1]) {
                inputs[1] = val;
                inavail[1] = true;
                return true;
            }
            return false;
        }
        
        int PullOutput() {
            if(!outavail)
                return -1;
            outavail = false;
            return output;
        }
        
        void ProcessInputs() {
            if(!IsInputAvailable())
                return;
            output = inputs[0] + inputs[1];
            outavail = true;
            inavail[0] = inavail[1] = false;
        }   
    virtual char get_node_id(){return 'A';}  
        
    private:
        int inputs[2];
        bool inavail[2];
        bool outavail;
        int output;
};

// Subtraction Node Class
class SNode : public Node {
    public:
        bool IsInputAvailable() {
            if(inavail[0] == inavail[1] == true)
               return true;
            return false;
        }
        
        bool IsOutputAvailable() {
            return outavail;
        }
        
        bool PushInput(int val) {
            if(!inavail[0]) {
                inputs[0] = val;
                inavail[0] = true;
                return true;
            }
            if (!inavail[1]) {
                inputs[1] = val;
                inavail[1] = true;
                return true;
            }
            return false;
        }
        
        int PullOutput() {
            if(!outavail)
                return -1;
            outavail = false;
            return output;
        }
        
        void ProcessInputs() {
            if(!IsInputAvailable())
                return;
            output = inputs[0] - inputs[1];
            outavail = true;
            inavail[0] = inavail[1] = false;
        }      
    virtual char get_node_id(){return 'S';}  
    
    private:
        int inputs[2];
        bool inavail[2];
        bool outavail;
        int output;

};

// Multiplication Node Class
class MNode : public Node {
    public :
        MNode(int _multconst, int _divconst) {
            multconst = _multconst;
            divconst = _divconst;
        }
        bool IsInputAvailable(){
            return inavail;
        }
        bool IsOutputAvailable() {
                return outavail;
        }
       bool PushInput(int val) {
            if(!inavail) {
                inavail = true;
                input = val;
                return true;
            } else {
                return false;
            }
        }
        int PullOutput() {
            if(outavail) {
                outavail = false;
                return output;
            }
            return 0;
        }    
        void ProcessInputs() {
            if(inavail) {
                inavail = false;
                output = input * multconst / divconst;
                outavail = true;
            }
            }
    virtual char get_node_id(){return 'M';}

    private:
        int multconst, divconst;
        int input, output;
        bool inavail, outavail;
};    

// Downsample Node Class
class DNode : public Node {
    public:
        DNode(int _nsample) {
            _downsample = _nsample;
        }


        bool IsInputAvailable(){
            return inavail;
        }

        bool IsOutputAvailable() {
            return outavail;
           }    

        bool PushInput(int val){
               if(!inavail) {
                inavail = true;
                input = val;
                return true;
            }
            return false;
        }

        int PullOutput() {
            if(outavail) {
                outavail = false;
                return output;
            }
            return -1;
        }

        void ProcessInputs() {
            if(inavail)    {
                inavail = false;
                input = output;
                outavail = true;
            }
        }

        int downsample() {
            return _downsample;
        }
    virtual char get_node_id(){return 'D';}

    private :
        int _downsample;
        int output, input;
        bool inavail, outavail;
};

// Upsample Node Class
class UNode : public Node {
    public:
        UNode(int _nsample) {
            upsample = _nsample;
        }

        bool IsInputAvailable(){
            return inavail;
        }

        bool IsOutputAvailable() {
            return outavail;
        }    

        bool PushInput(int val) {
            if(!inavail) {
                inavail = true;
                input = val;
                return true;
            }
            return false;
        }

        int PullOutput() {
            if(outavail) {
                outavail = false;
                return output;
            }
            return 0;
        } 
        
        int getNumSamples(){
            return upsample;
        }

        void ProcessInputs() {
                if(inavail) {
                inavail = false;
                output = input;
                outavail = true;
            }
        }
    virtual char get_node_id(){return 'U';}
    private:
        int upsample;
        int output, input;
        bool inavail, outavail;
};

// Fork Node Class
class FNode : public ONode {
       public:
            bool IsInputAvailable() {
                return inavail;
            }
    
            bool IsOutputAvailable() {
                return outavail;
            }
    
            bool PushInput(int val) {
               if(!inavail) {
                    input = val;
                    inavail = true;
                    return true;
                }else{
                    return false;
                }
            }
    
            int PullOutput() {
                if(outavail) {
                    outavail = false;
                    return output;
                }
                return -1;
            }
    
            void ProcessInputs() {
                if(inavail) {
                    output = input; 
                    inavail = true;
                    outavail = false;
                }
            }
        virtual char get_node_id(){return 'F';}
    private:
        bool inavail, outavail;
        int input, output;
};

// Constant Node Class
class CNode : public Node {
    // This is unimplemented
    public:
    bool IsInputAvailable(){
        return 0;
    }
    bool IsOutputAvailable() {
           return 0;
    }
    void PushInput(int val) {
    
    }
    int PullOutput() {
        return 0;
    }    
    void ProcessInputs() {
    
    }
    virtual char get_node_id(){return 'C';}
};

#endif
