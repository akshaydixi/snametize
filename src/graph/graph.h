// Copyright 2015 Akshay Dixit

#ifndef GRAPH_GRAPH_H_
#define GRAPH_GRAPH_H_

#include <cstdint>
#include <string>
#include <vector>

class Graph {
 private:
    bool _directedness;
 protected:
    bool _error;
 public:
    Graph();
    explicit Graph(bool);
    virtual inline ~Graph() = 0;
    virtual uint64_t getVertexCount() = 0;
    virtual uint64_t getEdgeCount() = 0;
    virtual void setErrorMessage(const std::string&) = 0;
    virtual bool ok();
    bool isDirected() { return _directedness; }
};

Graph::~Graph() {}

#endif // GRAPH_GRAPH_H_
