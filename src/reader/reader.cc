// Copyright 2015 Akshay Dixit

#include "reader.h"

Reader::Reader(const std::string& inputFilename) {
    inputFileBuffer.open(inputFilename);
}
