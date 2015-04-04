// Copyright 2015 Akshay Dixit

#include "writer.h"

Writer::Writer(const std::string& outputFileName) {
    outputFileBuffer.open(outputFileName);
}
