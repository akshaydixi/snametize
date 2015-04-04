// Copyright 2015 Akshay Dixit

#include <boost/program_options.hpp>
#include <chrono>
#include "snametize.h"
#include "writer/writer.h"
#include "writer/MetisWriter.h"
#include "writer/SnapWriter.h"
#include "writer/GmlWriter.h"

namespace po = boost::program_options;

int main(int argc, char** argv) {
    std::string input_file_path, output_file_path, output_format;
    std::string error_message = "Error\n";
    OutputFormat currentOutputFormat = METIS;
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
        ("help", "produce help message")
        ("input", po::value<std::string>(),
                "Path to the input webgraph file")
        ("output", po::value<std::string>(),
                "Path to which output file should be written")
        ("format", po::value<std::string>(),
                "Which format should the output file be written as. Currently we support SNAP, METIS and GML");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << std::endl;
            return 0;
        }

        if (vm.count("input"))
            input_file_path = vm["input"].as<std::string>();
        else
            error_message += "Please enter the path of the webgraph you want to convert\n";

        if (vm.count("output"))
            output_file_path = vm["output"].as<std::string>();
        else
            error_message += "Please enter the output path to store the converted graph\n";

        if (vm.count("format")) {
            std::string format = vm["format"].as<std::string>();
            if (format == "METIS")
                currentOutputFormat = METIS;
            else if (format == "SNAP")
                currentOutputFormat = SNAP;
            else if (format == "GML")
                currentOutputFormat = GML;
            else
                error_message+= "Please enter a valid output format: METIS, SNAP or GML\n";
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

    printf("Snametize v1.0\nInput File : %s\nOutput File : %s\n",
            input_file_path.c_str(),
            output_file_path.c_str());
    std::clock_t begin = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();

    std::ifstream webgraph(input_file_path);

    uint64_t vertices, edges = 0;
    std::vector< std::vector<uint64_t> > adjacency_list;
    std::string line;

    // Read the first line : Number of vertices
    getline(webgraph, line);
    std::string::size_type sz;
    vertices = std::stoi(line, &sz);

    // Read the raw webgraph file and increment each vertex by 1, and remove
    // self-loops because Metis doesn't like self-loops
    uint64_t vertex_counter = 1;
    NeighborFilterComparator comparator(vertex_counter);
    while (getline(webgraph, line)) {
        std::vector<uint64_t> neighbors;
        std::vector<uint64_t> filtered_neighbors;
        std::istringstream iss(line);
        std::vector<std::string> neighbors_string = split(line, ' ');
        std::transform(neighbors_string.begin(),
                neighbors_string.end(),
                std::back_inserter(neighbors),
                stringToMetisInteger);
        std::copy_if(neighbors.begin(),
                neighbors.end(),
                std::back_inserter(filtered_neighbors),
                comparator);
        edges+= filtered_neighbors.size();
        adjacency_list.push_back(filtered_neighbors);
        vertex_counter++;
        comparator.setVertex(vertex_counter);
    }

    webgraph.close();

    std::clock_t mid = std::clock();
    auto t_mid = std::chrono::high_resolution_clock::now();
    std::cout << std::fixed << std::setprecision(3)
            << "\n\nReading finished" << std::endl
            << "CPU Time used : "
            << 1000.0 * (mid - begin) / CLOCKS_PER_SEC
            << "ms" << std::endl
            << "Wall clock time passed : "
            << std::chrono::duration<double, std::milli>(t_mid-t_start).count()
            << "ms" << std::endl;

    Writer* writer;
    if (currentOutputFormat == METIS) {
        writer = new MetisWriter(output_file_path);
    } else if (currentOutputFormat == GML) {
        writer = new GmlWriter(output_file_path);
    } else if (currentOutputFormat == SNAP) {
        writer = new SnapWriter(output_file_path);
    }

    writer->write(adjacency_list, vertices, edges);
    std::clock_t end = std::clock();
    auto t_end = std::chrono::high_resolution_clock::now();
    std::cout << std::fixed << std::setprecision(3)
            << "\n\nWriting finished successfully" << std::endl
            << "CPU Time used : "
            << 1000.0 * (end - mid) / CLOCKS_PER_SEC
            << "ms" << std::endl
            << "Wall clock time passed : "
            << std::chrono::duration<double, std::milli>(t_end-t_mid).count()
            << "ms" << std::endl;
    std::cout << "Processing done" << std::endl;
}
