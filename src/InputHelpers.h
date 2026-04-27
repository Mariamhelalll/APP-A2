// File:       InputHelpers.h
// Author:     Maryam Mohamed 
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Robust user input helpers that re-prompt on bad
//             input instead of crashing or entering a bad state.

#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <sstream>

// Read a single integer from stdin. On bad input (non-numeric,
// EOF, etc.) clears the stream and re-prompts until success.
inline int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            // EOF or I/O failure: treat as 0 to avoid infinite loop
            std::cin.clear();
            return 0;
        }
        std::stringstream ss(line);
        if ((ss >> value) && (ss >> std::ws).eof()) {
            return value;
        }
        std::cout << "  [!] Please enter a valid whole number.\n";
    }
}

// Read a whole line of text. Trims leading/trailing whitespace.
inline std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cin.clear();
        return {};
    }
    // Trim whitespace
    const auto first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return {};
    const auto last = line.find_last_not_of(" \t\r\n");
    return line.substr(first, last - first + 1);
}