// Copyright 2015 Akshay Dixit
#ifndef SNAMETIZE_H_
#define SNAMETIZE_H_



#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

/* OutputFormats supported by Snametize. Currently, we support 

	1. METIS format : The first line will contain the number of vertices(N) and number of edges in the graph. 
					  N lines follow where each line i(1 <= i <= N) is a list of space separated vertices that
					  are connected to i

	2. SNAP format :  All the edges are placed line by line such that each edge is represented by
					   <vertex_id_in> <vertex_id_out>
	
	3. GML format :  Please refer to https://www.uni-passau.de/fileadmin/files/lehrstuhl/brandenburg/projekte/gml/gml-technical-report.pdf
					 for the Graph Modelling Language. We currently support only a ver basic GML format with no property support as of yet.
*/
enum OutputFormat {
    METIS = 1,
    SNAP = 2,
    GML = 3
};

// The Comparator class used to filter out edges from the graph the are
// self-loops
class NeighborFilterComparator {
 private:
        uint64_t _vertex;
 public:
        explicit NeighborFilterComparator(uint64_t vertex) {
            _vertex = vertex;
        }

        void setVertex(uint64_t new_vertex) {
            _vertex = new_vertex;
        }

        bool operator()(const uint64_t vertex) {
            return _vertex != vertex;
        }
};

// trim spaces from the end of a string
static inline std::string &rtrim(std::string* s) {
        s->erase(std::find_if(s->rbegin(),
                    s->rend(),
                    std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
                s->end());
        return *s;
}

// Split a string into a vector according to a delimiter
std::vector<std::string>& split(const std::string& s,
        const char& delim,
        std::vector<std::string>* elems);

std::vector<std::string> split(const std::string& s, const char& delim);

// Metis and Snap accepts vertex numbers from 1
// Webgraph stores vertices starting from 0
// Thus we increment all read numbers by 1
uint64_t inline stringToMetisInteger(const std::string& s) {
    return boost::lexical_cast<uint64_t>(s) + 1;
}

void writeMetisLine(std::ofstream* outputfile,
        const std::vector<uint64_t>& neighbors);

void writeSnapLines(std::ofstream* outputfile,
        const std::vector<uint64_t>& neighbors,
        const uint64_t& currentVertex);

void writeGmlLines(std::ofstream* outputfile,
        const std::vector<uint64_t>& neighbors,
        const uint64_t& currentVertex);

#endif  // SNAMETIZE_H_
