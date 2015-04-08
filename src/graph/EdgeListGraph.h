// Copyright 2015 Akshay Dixit

#ifndef GRAPH_EDGELISTGRAPH_H_
#define GRAPH_EDGELISTGRAPH_H_

#include "graph.h"
#include <unordered_set>
#include <unordered_map>

class EdgeListGraph : public Graph {
 private:
    // Whether this graph supports self loops or not. This is because
    // METIS doesn't support self loops, so with this we aim to not
    // read and store the self loop edges.
    bool self_loops;

    // The main structure of the graph is stored in the adjacencyList.
    std::unordered_map<uint64_t, std::unordered_set<uint64_t> > adjacencyList;

    // We're using an unordered_set here, because it gives O(1) access time on
    // an average case. We could have also used a regular map, or maintained
    // a list of seen vertices, but those would have taken O(log N) due to
    // binary search time for lookup.
    std::unordered_set <uint64_t> vertexSet;
 public:
    EdgeListGraph(bool directedness, bool self_loops);
    void addEdge(uint64_t, uint64_t);


};

#endif  // GRAPH_EDGELISTGRAPH_H_
