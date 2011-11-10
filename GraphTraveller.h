#ifndef GRAPHTRAVELLER_H
#include <queue>

#include "Node.h"
class GraphTraveller {
    public:
        static GraphTraveller* GetInstance() {
            if(_graph_traveller == NULL) {
                _graph_traveller = new GraphTraveller();
            }
            return _graph_traveller;
        }
        void TravelGraph() {
            // Travel the entire Graph
        }
    private:
        GraphTraveller() {}
        queue<Node*> _bfs_queue;
        // Singleton Instance
        static GraphTraveller* _graph_traveller;
};

GraphTraveller* GraphTraveller::_graph_traveller;
#endif
