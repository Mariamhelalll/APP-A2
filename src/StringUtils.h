// File:       StringUtils.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:   - Helper functions for string manipulation, such as splitting a string on a delimiter and performing case-insensitive substring searches.
//            - These utilities are used throughout the project for parsing input files and implementing search functionality in the resource and user lists.

#pragma once

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

namespace StringUtils {

    // Split a string on a delimiter character, returning the tokens.
    // Empty tokens (consecutive delimiters) are preserved, so callers can detect malformed lines by checking the token count.
    inline std::vector<std::string> split(const std::string& line, char delim) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    // Case-insensitive substring search. Returns true if 'needle' is found anywhere within 'haystack', ignoring case.
    // An empty needle is considered to be found.
    inline bool containsIgnoreCase(const std::string& haystack,
                                   const std::string& needle)
    {
        // If the needle is empty, we consider it to be found in any haystack (including an empty one). This is a common convention for substring search functions.
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

}  