// Copyright 2005 Akshay Dixit

#ifndef GMLWRITER_H_
#define GMLWRITER_H_

#include <sstream>
#include "writer.h"

void writeGmlLines(std::ofstream* outputfile,
        const std::vector<uint64_t>& neighbors,
        const uint64_t& currentVertex);

class GmlWriter : public Writer {
 public:
    explicit GmlWriter(const std::string& outputFilePath);
    void write(std::vector< std::vector<uint64_t> > adj_list,
            uint64_t vertices,
            uint64_t edges);

};

#endif  // GMLWRITER_H_
