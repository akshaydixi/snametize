// Copyright 2015 Akshay Dixit

#ifndef METISWRITER_H_
#define METISWRITER_H_

#include "../util/util.h"
#include <iterator>
#include <sstream>
#include "writer.h"

void writeMetisLine(std::ofstream* outputfile,
            const std::vector<uint64_t>& neighbors);

class MetisWriter : public Writer {
 public:
    explicit MetisWriter(const std::string& outputFilePath);
    void write(std::vector< std::vector<uint64_t> > adj_list,
            uint64_t vertices,
            uint64_t edges);
};

#endif /* METISWRITER_H_ */
