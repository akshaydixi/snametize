// Copyright 2015 Akshay Dixit

#ifndef SNAPREADER_H_
#define SNAPREADER_H_

#include "reader.h"

class SnapReader : public Reader {
public:
    explicit SnapReader(const std::string& inputFilename)
            : Reader(inputFilename) {}

    void read(Graph*);
};

#endif /* SNAPREADER_H_ */
