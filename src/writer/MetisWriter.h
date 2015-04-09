// Copyright 2015 Akshay Dixit

#ifndef WRITER_METISWRITER_H_
#define WRITER_METISWRITER_H_

#include "../util/util.h"
#include "../graph/graph.h"
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include "writer.h"

void writeMetisLine(std::ofstream* outputfile,
            const std::vector<uint64_t>& neighbors);

class MetisWriter : public Writer {
 public:
    explicit MetisWriter(const std::string& outputFilePath);
    void write(std::vector< std::vector<uint64_t> > adj_list,
            uint64_t vertices,
            uint64_t edges);
    void newWrite(Graph*);
};

#endif  // WRITER_METISWRITER_H_
