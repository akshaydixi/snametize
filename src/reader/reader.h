// Copyright 2015 Akshay Dixit

#ifndef READER_READER_H_
#define READER_READER_H_

#include <fstream>
#include <string>
#include "../graph/graph.h"

class Reader {
 public:
    explicit Reader(const std::string& inputFilename);
    virtual inline ~Reader() = 0;

    virtual void read(Graph*) = 0;

    std::ifstream inputFileBuffer;
};

Reader::~Reader() {
    inputFileBuffer.close();
}

#endif  // READER_READER_H_
