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

    if(this->adjacencyList.find(v1) != this->adjacencyList.end()) {
        // Check if you've already added this edge before. If so, do not
        // update the number of edges.
        std::vector<uint64_t> v1EdgeList = this->adjacencyList[v1];
        if (std::find(v1EdgeList.begin(), v1EdgeList.end(), v2) == v1EdgeList.end()) {
            v1EdgeList.push_back(v2);
            this->vertexSet.insert(v2);
            if (v2 > maxVertex) maxVertex = v2;
            this->edges++;
        }
    } else {
        std::vector<uint64_t> tmpVector = {v2};
        this->adjacencyList[v1] = tmpVector;
        this->vertexSet.insert({v1,v2});
        this->edges++;
        uint64_t tmpMax = v1 > v2 ? v1 : v2;
        if (maxVertex < tmpMax) maxVertex = tmpMax;
    }
}

void EdgeListGraph::getEdgeList(uint64_t vertex,
        std::vector<uint64_t>* edgeList) {
    edgeList =  &(this->adjacencyList[vertex]);
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
