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
        	return inavail;
      	}

    	bool IsOutputAvailable() {
       		return outavail;
    	}

    	void PushInput(int val) {
    		if(!inavail) {
				input = val;
				inavail = true;
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
			else 
				printf("Cannot Schedule \n");
    	}
	private:
		bool inavail;
		bool outavail;
		int input;
		int output;
};

class ONode : public Node {
    public:
    	bool IsInputAvailable() {
        	return inavail;
    	}

    	bool IsOutputAvailable() {
        	return outavail;
    	}

    	void PushInput(int val) {
   			if(!inavail) {
				input = val;
				inavail = true;
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
    		if(inputavail) {
				output = input; 
				inavail = true;
				outavail = false;
			}
    	}
	private:
		bool inavail, outavail;
		int input, output;
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
    
    private:
        int inputs[2];
        bool inavail[2];
        bool outavail;
        int output;

};

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
   		void PushInput(int val) {
    		if(!inavail) {
				inavail = true;
				input = val;
			} else {
				printf("Schedule Error");
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

	private:
		int multconst, divconst;
		int input, output;
		bool inavail, outavail;
};	

class DNode : public Node {
    public:
		DNode(int _nsample) {
			downsample = _nsample;
		}


    	bool IsInputAvailable(){
        	return inavail;
    	}

    	bool IsOutputAvailable() {
        	return outavail;
   		}	

    	void PushInput(int val){
       		if(!inavail) {
				inavail = true;
				input = val;
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
    		if(inavail)	{
				inavail = false;
				input = output;
				outavail = true;
			}
    	}

		int downsample() {
			return downsample;
		}

	private :
		int downsample;
		int output, input;
		bool inavail, outavail;
};

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

    	void PushInput(int val) {
    		if(!inavail) {
				inavail = true;
				input = val
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
				output = input;
				outavail = true;
			}
    	}

	private:
		int n;
		int output, input;
		bool inavail, outavail;
};


class FNode : public ONode {
    public:
    bool IsInputAvailable(){
        return ONode::IsInputAvailable();
    }
    bool IsOutputAvailable() {
        return ONodeIsOutputAvailable();
    }
    void PushInput(int val) {
    	ONOde:
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
