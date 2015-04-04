// Copyright 2015 Akshay Dixit

#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>

// Trim spaces from the end of a string
static inline std::string &rtrim(std::string* s) {
        s->erase(std::find_if(s->rbegin(),
                    s->rend(),
                    std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
                s->end());
        return *s;
}

// Split a string into a vector according to a delimiter
std::vector<std::string>& split(const std::string& s,
        const char& delim,
        std::vector<std::string>* elems);

std::vector<std::string> split(const std::string& s, const char& delim);

#endif  // UTIL_UTIL_H_
