#ifndef NODE_H
#define NODE_H
class Node {
    public:
        virtual void ProcessInputs() = 0;
        virtual bool IsInputAvailable() = 0;
        virtual bool IsOutputAvailable() = 0;
        virtual void PushInput(int val) = 0;
        virtual int PullOutput() = 0;
        Node () {
            _nodeno = NodeNoCount++;
        }
        int get_node_no() { return _nodeno;}
    private:
        int _nodeno;
        static int NodeNoCount;        
};

int Node::NodeNoCount;

class INode : public Node {
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
};

class ONode : public Node {
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

};

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
        
        void PushInput(int val) {
            if(!inavail[0]) {
                inputs[0] = val;
                inavail[0] = true;
            }
            if (!inavail[1]) {
                inputs[1] = val;
                inavail[1] = true;
            }
        }
        
        int PullOutput() {
            if(!outavail)
                return -1;
            outavail = true;
            return output;
        }
        
        void ProcessInputs() {
            if(!IsInputAvailable())
                return;
            output = inputs[0] + inputs[1];
            outavail = true;
            inavail[0] = inavail[1] = false;
        }     
        
    private:
        int inputs[2];
        bool inavail[2];
        bool outavail;
        int output;
};

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
        
        void PushInput(int val) {
            if(!inavail[0]) {
                inputs[0] = val;
                inavail[0] = true;
            }
            if (!inavail[1]) {
                inputs[1] = val;
                inavail[1] = true;
            }
        }
        
        int PullOutput() {
            if(!outavail)
                return -1;
            outavail = true;
            return output;
        }
        
        void ProcessInputs() {
            if(!IsInputAvailable())
                return;
            output = inputs[0] - inputs[1];
            outavail = true;
            inavail[0] = inavail[1] = false;
        }        
    
    private:
        int inputs[2];
        bool inavail[2];
        bool outavail;
        int output;

};

class MNode : public Node {
    public :
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
};

class DNode : public Node {
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
};

class UNode : public Node {
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
};


class FNode : public Node {
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
};

class CNode : public Node {
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
};

#endif
