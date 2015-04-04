// Copyright 2015 Akshay Dixit

#include "SnapWriter.h"

void writeSnapLines(std::ofstream* outputfile,
        const std::vector<uint64_t>& neighbors,
        const uint64_t& currentVertex) {
    std::stringstream edge_list_stream;
    for (auto neighbor : neighbors)
        edge_list_stream << currentVertex << " " << neighbor << std::endl;
    std::string edge_list_string = edge_list_stream.str().c_str();
    *outputfile << edge_list_string;
}

SnapWriter::SnapWriter(const std::string& outputFilePath)
        : Writer(outputFilePath) {}

void SnapWriter::write(std::vector< std::vector<uint64_t> > adj_list,
            uint64_t vertices,
            uint64_t edges) {
    uint64_t currentVertex = 1;
    for (std::vector<uint64_t> neighbors : adj_list) {
        writeSnapLines(&outputFileBuffer, neighbors, currentVertex);
        ++currentVertex;
    }
}
