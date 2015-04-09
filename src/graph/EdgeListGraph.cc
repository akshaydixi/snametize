// Copyright 2015 Akshay Dixit

#include "EdgeListGraph.h"

EdgeListGraph::EdgeListGraph(bool directedness, bool self_loops)
        : Graph(directedness) {
    this->self_loops = self_loops;
    this->edges = 0;
}

void EdgeListGraph::addEdge(uint64_t v1, uint64_t v2) {

    // Don't process self loop edges, if we don't plan on suppporting them
    if (v2 == v1 && !this->self_loops) return;


    if(this->vertexSet.find(v1) != this->vertexSet.end() &&
            this->adjacencyList.find(v1) != this->adjacencyList.end()) {
        // Check if you've already added this edge before. If so, do not
        // update the number of edges.
        if (this->adjacencyList[v1].find(v2) != this->adjacencyList[v1].end()) {
            this->adjacencyList[v1].insert(v2);
            this->edges++;
        }
    } else {
        this->adjacencyList[v1] = std::unordered_set<uint64_t>({v2});
        this->vertexSet.insert({v1,v2});
        this->edges++;
    }
}

void EdgeListGraph::getEdgeList(uint64_t vertex,
        std::vector<uint64_t>* edgeList) {
    std::copy(this->adjacencyList[vertex].begin(),
            this->adjacencyList[vertex].end(),
            std::back_inserter(*edgeList));
}

uint64_t EdgeListGraph::getVertexCount() {
    return this->vertexSet.size();
}

uint64_t EdgeListGraph::getEdgeCount() {
    return this->edges;
}

void EdgeListGraph::getVertices(std::vector<uint64_t>* vertices) {
    std::copy(this->vertexSet.begin(),
            this->vertexSet.end(),
            std::back_inserter(*vertices));
}

void EdgeListGraph::setErrorMessage(const std::string& errorMessage) {
    _error = true;
    this->errorMessage = errorMessage;
}
