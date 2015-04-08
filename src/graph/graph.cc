// Copyright 2015 Akshay Dixit

#include "graph.h"

// We assume that the graph is undirected by default
Graph::Graph() : Graph::Graph(false) {}

Graph::Graph(bool directedness) {
    _directedness = directedness;
}
