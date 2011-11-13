#ifndef EDGE_H
#define EDGE_H

#include "Graph.h"
#define MAX_BUFF_LEN 10

// Node Template -- to be inherited
class Edge {
    public:
        // Construction operations
        Edge(int id){
            // these must be set
            _id = id;
            _from = -1;
            _to = -1;
            // these are defaults
            _buffLen = 1;
            _head = 0;
            _tail = 0;
            _numQueued = 0;
            _hasDelay = false;
        }
        int getId(){
            return _id;
        }
        void enterOutput(int nodeno){
            _to = nodeno;
        }
        void enterInput(int nodeno){
            _from = nodeno;
        }
        int getOutput(){
            return _to;
        }
        int getInput(){
            return _from;
        }
        
        // Ring Buffer operations
        void enterDelay(int delay){
            _hasDelay = true;
            _buffLen = delay;
            _head = 0;
            _tail = 0;
        }
        // this is to account for up/down sampling nodes
        void addPadding(int delay){
            if(delay > _buffLen)
            _buffLen = delay;
            _head = 0;
            _tail = 0;
        }
        bool hasDelay(){
            return _hasDelay;
        }
        void push(int val){
            _buffer[_head] = val;
            _numQueued++;
            _head = (_head+1)%_buffLen;
        }
        int pop(){
            int val = _buffer[_tail];
            _numQueued--;
            _tail = (_tail+1)%_buffLen;
            return val;
        }
        
        // Pushing and Popping tests
        int numPushable(){
            return(_buffLen - _numQueued);
        }
        int numPoppable(){
            return(_numQueued);
        }
        int bufferSize(){
            return(_buffLen);
        }

    private:
        int _id;
        int _from;
        int _to;
        int _buffLen;
        int _buffer[MAX_BUFF_LEN];
        int _head;
        int _tail;
        int _numQueued;
        bool _hasDelay;
              
};

#endif