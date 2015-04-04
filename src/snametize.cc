// Copyright 2015 Akshay Dixit
#include "snametize.h"

std::vector<std::string>& split(const std::string& s,
        const char& delim,
        std::vector<std::string>* elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
         elems->push_back(item);
    }
    return *elems;
}

std::vector<std::string> split(const std::string& s, const char& delim) {
    std::vector<std::string> elems;
    split(s, delim, &elems);
    return elems;
}

void writeMetisLine(std::ofstream* outputfile,
        const std::vector<uint64_t>& neighbors) {
    std::stringstream node_list_stream;
    std::copy(neighbors.begin(),
            neighbors.end(),
            std::ostream_iterator<uint64_t>(node_list_stream, " "));
    std::string untrimmed_neighbor_str = node_list_stream.str().c_str();
    *outputfile << rtrim(&untrimmed_neighbor_str) << std::endl;
}

void writeSnapLines(std::ofstream* outputfile,
        const std::vector<uint64_t>& neighbors,
        const uint64_t& currentVertex) {
    std::stringstream edge_list_stream;
    for (auto neighbor : neighbors)
        edge_list_stream << currentVertex << " " << neighbor << std::endl;
    std::string edge_list_string = edge_list_stream.str().c_str();
    *outputfile << edge_list_string;
}

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
