// Copyright 2015 Akshay Dixit

#include "GmlWriter.h"

void writeGmlLines(std::ofstream* outputfile,
        const std::vector<uint64_t>& neighbors,
        const uint64_t& currentVertex) {
    std::stringstream gml_stream;
    static uint64_t edge_counter = 1;
    gml_stream << "node [" << std::endl
            << "id " << currentVertex << std::endl
            << "]" << std::endl;
    for (auto neighbor : neighbors)
        gml_stream <<  "edge [" << std::endl
            << "id " << edge_counter++ << std::endl
            << "source " << currentVertex << std::endl
            << "target" << neighbor << std::endl
            << "]" << std::endl;
    std::string gml_stream_string = gml_stream.str().c_str();
    *outputfile << gml_stream_string;
}

GmlWriter::GmlWriter(const std::string& outputFilePath)
        : Writer(outputFilePath) {}

void GmlWriter::write(std::vector< std::vector<uint64_t> > adj_list,
        uint64_t vertices,
        uint64_t edges) {
    std::stringstream ss;
    ss << "graph [" << std::endl
           << "directed 0" << std::endl
           << "vertex_properties [" << std::endl
           << "]" << std::endl
           << "edge_properties [" << std::endl
           << "]" << std::endl;
    outputFileBuffer << ss.str().c_str();
    uint64_t currentVertex = 1;
    for (std::vector<uint64_t> neighbors : adj_list) {
        writeGmlLines(&outputFileBuffer, neighbors, currentVertex);
        ++currentVertex;
    }
}
