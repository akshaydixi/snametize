// Copyright 2015 Akshay Dixit

#ifndef WRITER_WRITER_H_
#define WRITER_WRITER_H_

#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

class Writer {
 public:
    explicit Writer(const std::string& outputFileName);
    virtual inline ~Writer() = 0;

    virtual void write(std::vector< std::vector<uint64_t> >,
            uint64_t,
            uint64_t) = 0;

    std::ofstream outputFileBuffer;
};

Writer::~Writer() {
    outputFileBuffer.close();
}

#endif  // WRITER_WRITER_H_
