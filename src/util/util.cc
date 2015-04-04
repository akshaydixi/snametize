// Copyright 2015 Akshay Dixit

#include "util.h"

std::vector<std::string>& split(const std::string& s,
        const char& delim,
        std::vector<std::string>* elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
         elems->push_back(item);
    }
    return *elems;
}

std::vector<std::string> split(const std::string& s, const char& delim) {
    std::vector<std::string> elems;
    split(s, delim, &elems);
    return elems;
}
