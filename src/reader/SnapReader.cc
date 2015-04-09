// Copyright 2015 Akshay Dixit

#include "SnapReader.h"
#include <boost/lexical_cast.hpp>
#include "../util/util.h"
#include "../graph/EdgeListGraph.h"

void SnapReader::read(Graph* graph) {
    EdgeListGraph* elGraph = dynamic_cast<EdgeListGraph*>(graph);
    elGraph = new EdgeListGraph(false, false);
    std::string line;
    uint64_t lineNumber = 1;
    while(getline(inputFileBuffer, line)) {
        std::size_t found = line.find_first_not_of(" \t");
        if (found != std::string::npos &&
                line[found] == '/' &&
                line[found + 1] == '/' ) continue;
        std::vector<std::string> edgeList = split(line, ' ');

        // Verify that the format of the SNAP file we are reading is correct
        // and exit if its not.
        if (edgeList.size() != 2) {
            std::stringstream errorMessageStream;
            errorMessageStream << "Error" << std::endl
                    << "Wrong format of SNAP file given" << std::endl
                    << "Number of vertices found in line " << lineNumber
                    << " are" << edgeList.size();
            std::string errorMessage = errorMessageStream.str();
            elGraph->setErrorMessage(errorMessage);
        }
        elGraph->addEdge(boost::lexical_cast<uint64_t>(edgeList[0]),
                boost::lexical_cast<uint64_t>(edgeList[1]));
        ++lineNumber;
    }
}
