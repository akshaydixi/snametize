// Copyright 2015 Akshay Dixit

#include "MetisWriter.h"
#include "../util/util.h"
#include "../graph/EdgeListGraph.h"

void writeMetisLine(std::ofstream* outputfile,
            const std::vector<uint64_t>& neighbors) {
        std::stringstream node_list_stream;
        std::copy(neighbors.begin(),
                neighbors.end(),
                std::ostream_iterator<uint64_t>(node_list_stream, " "));
        std::string untrimmed_neighbor_str = node_list_stream.str().c_str();
        *outputfile << rtrim(&untrimmed_neighbor_str) << std::endl;
    }

MetisWriter::MetisWriter(const std::string& outputFilePath)
        : Writer(outputFilePath) {}

void MetisWriter::write(std::vector< std::vector<uint64_t> > adj_list,
        uint64_t vertices,
        uint64_t edges) {
    outputFileBuffer << vertices << " " << edges << std::endl;
    for (std::vector<uint64_t> neighbors : adj_list) {
        writeMetisLine(&outputFileBuffer, neighbors);
    }
}

void MetisWriter::newWrite(Graph* graph) {
    EdgeListGraph* elGraph = dynamic_cast<EdgeListGraph*>(graph);
    uint64_t num_edges = elGraph->getEdgeCount();
    uint64_t num_vertices = elGraph->maxVertex;
    if (!elGraph->isDirected()) num_edges/= 2;
    outputFileBuffer << num_vertices << " " << num_edges << std::endl;
    std::vector<uint64_t>* edgeList = new std::vector<uint64_t>();
    for (uint64_t i = 1; i <= num_vertices; i++ ) {
        std::vector<uint64_t>* edgeList = new std::vector<uint64_t>();
        elGraph->getEdgeList(i,edgeList);
        writeMetisLine(&outputFileBuffer, *edgeList);
        edgeList->clear();
    }
}
