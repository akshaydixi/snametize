/* 
Author : Akshay Dixit (hello@akshaydixi.me)
Version : 0.0.1
LICENSE : MIT License
*/

#include "snametize.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;

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

void writeGmlLines(std::ofstream& outputfile, std::vector<uint64_t>& neighbors, uint64_t& currentVertex) {
	std::stringstream gml_stream;
	static uint64_t edge_counter = 1;
	gml_stream << "node [" << std::endl << "id " << currentVertex << std::endl << "]" << std::endl;
	for (auto neighbor : neighbors) gml_stream <<  "edge [" << std::endl
		<< "id " << edge_counter++ << std::endl 
		<< "source " << currentVertex << std::endl 
		<< "target" << neighbor << std::endl
		<< "]" << std::endl;
	std::string gml_stream_string = gml_stream.str().c_str();
	outputfile << gml_stream_string;
}

int main(int argc, char** argv) {
	
	std::string input_file_path, output_file_path, output_format, error_message = "Error\n";
	OutputFormat currentOutputFormat = METIS;
	try {
		po::options_description desc("Allowed options");
		desc.add_options()
			("help", "produce help message")
			("input", po::value<std::string>(), "Path to the input webgraph file")
			("output", po::value<std::string>(), "Path to which output file should be written")
			("format", po::value<std::string>(), "Which format should the output file be written as. Currently we support SNAP, METIS and GML")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc << std::endl;
			return 0;
		}

		if (vm.count("input")) input_file_path = vm["input"].as<std::string>();
		else error_message += "Please enter the path of the webgraph you want to convert\n";

		if (vm.count("output")) output_file_path = vm["output"].as<std::string>();
		else error_message += "Please enter the output path to store the converted graph\n";

		if (vm.count("format")) {
			std::string format = vm["format"].as<std::string>();
			if (format == "METIS") currentOutputFormat = METIS;
			else if (format == "SNAP") currentOutputFormat = SNAP;
			else if (format == "GML") currentOutputFormat = GML;
			else error_message+= "Please enter a valid output format: METIS, SNAP or GML\n";
		}

		if (error_message.compare("Error\n") != 0) {
			std::cerr << error_message;
			return 1;
		} 
		
	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	} catch(...) {
		std::cerr << "Exception of unknown type!!" << std::endl;
	}
	
	printf("Snametize v1.0\nInput File : %s\nOutput File : %s\n", input_file_path.c_str(), output_file_path.c_str());
	std::clock_t begin = std::clock();
	auto t_start = std::chrono::high_resolution_clock::now();

	std::ifstream webgraph(input_file_path);

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

	std::ofstream outputfile(output_file_path);
	 
	if (currentOutputFormat == METIS) {
		std::stringstream ss;
		ss << vertices << " " << edges;
		outputfile << ss.str().c_str() << std::endl;
	} else if (currentOutputFormat == GML) {
		std::stringstream ss;
		ss << "graph [" << std::endl
		   << "directed 0" << std::endl
		   << "vertex_properties [" << std::endl
		   << "]" << std::endl
		   << "edge_properties [" << std::endl
		   << "]" << std::endl;
		outputfile << ss.str().c_str();
	}
	
	uint64_t currentVertex = 1;
	for (std::vector<uint64_t> neighbors : adjacency_list) {
		if (currentOutputFormat == METIS) {
			writeMetisLine(outputfile, neighbors);
		} else if (currentOutputFormat == SNAP) {
			writeSnapLines(outputfile, neighbors, currentVertex);
			currentVertex++;
		} else if (currentOutputFormat == GML) {
			writeGmlLines(outputfile, neighbors, currentVertex);
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