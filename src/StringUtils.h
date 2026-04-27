// File:       StringUtils.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Header-only string utilities shared across the
//             project. Centralising the split() helper here
//             removes the duplicate that existed in both
//             ResourceList.cpp and UserList.cpp (Day 6 DRY fix).

#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

namespace StringUtils {

    // Split a string on a delimiter character, returning the tokens.
    // Empty tokens (consecutive delimiters) are preserved, so callers
    // can detect malformed lines by checking the token count.
    inline std::vector<std::string> split(const std::string& line, char delim) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    // Case-insensitive substring search. Returns true if
    // `needle` appears anywhere inside `haystack`, ignoring case.
    // An empty needle matches by convention.
    inline bool containsIgnoreCase(const std::string& haystack,
                                   const std::string& needle)
    {
        if (needle.empty()) return true;
        const auto it = std::search(
            haystack.begin(), haystack.end(),
            needle.begin(),   needle.end(),
            [](char a, char b) {
                return std::tolower(static_cast<unsigned char>(a)) ==
                       std::tolower(static_cast<unsigned char>(b));
            });
        return it != haystack.end();
    }

}  // namespace StringUtils