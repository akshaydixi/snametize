// Copyright 2015 Akshay Dixit

#include "MetisWriter.h"
#include "../util/util.h"

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
