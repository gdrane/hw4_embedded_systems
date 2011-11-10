#ifndef EDGE_H
#define EDGE_H
class Edge {
    public:
        Edge(int from_node, int to_node, int delay) {
            _from_node = from_node;
            _to_node = to_node;
            _delay = delay;
            _edge_no = ++_edgecount;
        }
        
        Edge(int from_node, int to_node) {
            _from_node = from_node;
            _to_node = to_node;
            _edge_no = ++_edgecount;
        }
        
        int from_node() { return _from_node;}
        int to_node() { return _to_node; }
        
    private:
        int _edge_no;
        int _from_node;
        int _to_node;
        int _delay;
        static int _edgecount;

};

int Edge::_edgecount;
#endif
