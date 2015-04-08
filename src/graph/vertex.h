// Copyright 2015 Akshay Dixit

#ifndef GRAPH_VERTEX_H_
#define GRAPH_VERTEX_H_

class Vertex {
 public:
    Vertex();
    virtual inline ~Vertex() = 0;
};

Vertex::~Vertex() {}

#endif  // GRAPH_VERTEX_H_
