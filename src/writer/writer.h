// Copyright 2015 Akshay Dixit
#ifndef WRITER_H_
#define WRITER_H_

#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

class Writer {
 public:
    Writer(const std::string& outputFileName);
    virtual inline ~Writer() = 0;

    virtual void write(std::vector< std::vector<uint64_t> >,
            uint64_t,
            uint64_t) = 0;

    std::ofstream outputFileBuffer;
};

Writer::~Writer() {
    outputFileBuffer.close();
}

#endif /* WRITER_H_ */
