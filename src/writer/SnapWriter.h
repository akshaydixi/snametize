// Copyright 2015 Akshay Dixit

#ifndef SNAPWRITER_H_
#define SNAPWRITER_H_

#include <sstream>
#include "writer.h"

void writeSnapLines(std::ofstream* outputfile,
            const std::vector<uint64_t>& neighbors);

class SnapWriter : public Writer {
 public:
    explicit SnapWriter(const std::string& outputFilePath);
    void write(std::vector< std::vector<uint64_t> > adj_list,
            uint64_t vertices,
            uint64_t edges);
};

#endif /* SNAPWRITER_H_ */
