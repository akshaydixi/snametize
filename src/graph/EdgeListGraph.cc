// Copyright 2015 Akshay Dixit

#include "EdgeListGraph.h"

EdgeListGraph::EdgeListGraph(bool directedness, bool self_loops)
        : Graph(directedness) {
    this.self_loops = self_loops;
}

void EdgeListGraph::addEdge(uint64_t v1, uint64_t v2) {

    // Don't process self loop edges, if we don't plan on suppporting them
    if (v2 == v1 && !this.self_loops) return;


    if(this.vertexSet.find(v1) != this.vertexSet.end()) {
        this.adjacencyList[v1].insert(v2);
    } else {
        this.adjacencyList.insert(
                std::make_pair<uint64_t, std::unordered_set<uint64_t> > (
                        v1, std::unordered_set({v2}) ));
        this.vertexSet.insert(v1);
    }
}


