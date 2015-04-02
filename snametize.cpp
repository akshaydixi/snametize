/* 
Author : Akshay Dixit (hello@akshaydixi.me)
Version : 0.0.1
LICENSE : MIT License
*/

#include "snametize.hpp"

void writeMetisLine(std::ofstream& outputfile, std::vector<uint64_t>& neighbors) {
	std::stringstream node_list_stream;
	std::copy(neighbors.begin(), neighbors.end(), std::ostream_iterator<uint64_t>(node_list_stream, " "));
	std::string untrimmed_neighbor_str = node_list_stream.str().c_str();
	outputfile << rtrim(untrimmed_neighbor_str) << std::endl;
}

void writeSnapLines(std::ofstream& outputfile, std::vector<uint64_t>& neighbors, uint64_t& currentVertex) {
	std::stringstream edge_list_stream;
	for (auto neighbor : neighbors)	edge_list_stream << currentVertex << " " << neighbor << std::endl;
	std::string edge_list_string = edge_list_stream.str().c_str();
	outputfile << edge_list_string;
}


int main(int argc, char** argv) {
	if (argc < 3) {
		printf("Usage: ./snametize <raw_webgraph_file> <new_metis_or_snap_file(> [--snap] \nUnless you specify the option '--snap', we convert to the metis format by default\n");
		return 1;
	}

	printf("Snametize v1.0\nInput File : %s\nOutput File : %s\n", argv[1], argv[2]);
	std::clock_t begin = std::clock();
	auto t_start = std::chrono::high_resolution_clock::now();

	std::ifstream webgraph(argv[1]);

	uint64_t vertices,edges = 0;
	std::vector< std::vector<uint64_t> > adjacency_list;
	std::string line;
	
	// Read the first line : Number of vertices
	getline(webgraph, line);
	std::string::size_type sz;
	vertices = std::stoi(line, &sz);

	// Read the raw webgraph file and increment each vertex by 1, and remove self-loops because Metis doesn't like self-loops
	uint64_t vertex_counter = 1;
	NeighborFilterComparator comparator(vertex_counter);
	while(getline(webgraph, line)) {
		std::vector<uint64_t> neighbors;
		std::vector<uint64_t> filtered_neighbors;
		std::istringstream iss(line);
		std::vector<std::string> neighbors_string = split(line, ' ');
		std::transform(neighbors_string.begin(),neighbors_string.end(), std::back_inserter(neighbors),stringToMetisInteger);
		std::copy_if(neighbors.begin(), neighbors.end(), std::back_inserter(filtered_neighbors), comparator);
		edges+= filtered_neighbors.size();
		adjacency_list.push_back(filtered_neighbors);
		vertex_counter++;
		comparator.setVertex(vertex_counter);
	}

	webgraph.close();
	
	std::clock_t mid = std::clock();
	auto t_mid = std::chrono::high_resolution_clock::now();
	std::cout << std::fixed << std::setprecision(3) << "\n\n\nReading finished" << std::endl
			  << "CPU Time used : " << 1000.0 * (mid - begin) / CLOCKS_PER_SEC << "ms" << std::endl
			  << "Wall clock time passed : " << std::chrono::duration<double, std::milli>(t_mid - t_start).count()
			  << "ms" << std::endl;

	std::ofstream outputfile(argv[2]);
	OutputFormat currentOutputFormat = METIS;
	if (argc == 4 && SNAP_OPTION.compare(argv[3]) == 0) {
		currentOutputFormat = SNAP;
	}
	 
	if (currentOutputFormat == METIS) {
		std::stringstream ss;
		ss << vertices << " " << edges;
		outputfile << ss.str().c_str() << std::endl;
	}
	
	uint64_t currentVertex = 1;
	for (std::vector<uint64_t> neighbors : adjacency_list) {
		if (currentOutputFormat == METIS) {
			writeMetisLine(outputfile, neighbors);
		} else if (currentOutputFormat == SNAP) {
			writeSnapLines(outputfile, neighbors, currentVertex);
			currentVertex++;
		}
	}

	outputfile.close();

	std::clock_t end = std::clock();
	auto t_end = std::chrono::high_resolution_clock::now();
	std::cout << std::fixed << std::setprecision(3) << "\n\n\nWriting finished" << std::endl
			  << "CPU Time used : " << 1000.0 * (end - mid) / CLOCKS_PER_SEC << "ms" << std::endl
			  << "Wall clock time passed : " << std::chrono::duration<double, std::milli>(t_end- t_mid).count()
			  << "ms" << std::endl;

	printf("\nProcessing done\n");

}