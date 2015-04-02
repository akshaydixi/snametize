#ifndef SNAMETIZE_HPP
#define SNAMETIZE_HPP


#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

/* OutputFormats supported by Snametize. Currently, we support 

	1. Metis format : The first line will contain the number of vertices(N) and number of edges in the graph. 
					  N lines follow where each line i(1 <= i <= N) is a list of space separated vertices that
					  are connected to i

	2. SNAP format :  All the edges are placed line by line such that each edge is represented by
					   <vertex_id_in> <vertex_id_out>
	*/
enum OutputFormat {
	METIS = 1,
	SNAP = 2,
};

// The Comparator class used to filter out edges from the graph the are self-loops
class NeighborFilterComparator {
	private:
	 uint64_t _vertex;
	public:
		NeighborFilterComparator(uint64_t vertex) {
			_vertex = vertex;
		}
		void setVertex(uint64_t new_vertex) {
			_vertex = new_vertex;
		}

		bool operator()(const uint64_t vertex) {
			return _vertex != vertex;
		}
};

// Option to check for SNAP output argument
const std::string SNAP_OPTION("--snap");

// trim spaces from the end of a string
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

// Split a string into a vector according to a delimiter
std::vector<std::string>& split(const std::string& s, char delim, std::vector<std::string>& elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;	
}

std::vector<std::string> split(const std::string& s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

// Metis and Snap accepts vertex numbers from 1
// Webgraph stores vertices starting from 0
// Thus we increment all read numbers by 1
uint64_t stringToMetisInteger(const std::string& s) {
	return boost::lexical_cast<uint64_t>(s) + 1;
}

void writeMetisLine(std::ofstream& outputfile, std::vector<uint64_t>& neighbors);
void writeSnapLines(std::ofstream& outputfile, std::vector<uint64_t>& neighbors, uint64_t& currentVertex);

#endif // SNAMETIZE_HPP