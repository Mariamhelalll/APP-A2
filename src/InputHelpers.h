// File:       InputHelpers.h
// Author:     Maryam Mohamed 
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Helper functions for robust user input handling. These functions will repeatedly prompt the user until valid input is received, preventing common issues like non-numeric input when an integer is expected. They also trim whitespace from string inputs.
#pragma once

#include <iostream>
#include <limits>
#include <string>
#include <sstream>

// Read a single integer from input. 
// On bad input (non-numeric,EOF, etc), it clears the stream and re-prompts until successful input is entered.
inline int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::string line;
        if (!std::getline(std::cin, line)) {
            // EOF or I/O failure is treated as 0 to avoid infinite loop.
            std::cin.clear();
            return 0;
        }
        //  stringstream is used to validate that the entire line is a valid integer (no extra characters).
        std::stringstream ss(line);
        if ((ss >> value) && (ss >> std::ws).eof()) {
            return value;
        }
        std::cout << "  [!] Please enter a valid whole number.\n";
    }
}

// Read a whole line of text + trimming the leading/trailing whitespace.
inline std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    if (!std::getline(std::cin, line)) {
        std::cin.clear();
        return {};
    }
    // Trimming of whitespace
    const auto first = line.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return {};
    const auto last = line.find_last_not_of(" \t\r\n");
    return line.substr(first, last - first + 1);
}