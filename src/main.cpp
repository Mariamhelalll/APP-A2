// =============================================================
// File:       main.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Day 2 entry point. Loads resources and users from
//             text files and prints them to verify the factory
//             pattern and polymorphic output.
// =============================================================
#include <iostream>
#include <stdexcept>

#include "ResourceList.h"
#include "UserList.h"

int main() {
    std::cout << "===============================================\n"
              << "  University Library Management System\n"
              << "  Staff: Librarian (Maryam Mohamed)\n"
              << "===============================================\n\n";

    try {
        ResourceList resources("data/resources.txt");
        UserList     users("data/users.txt");

        std::cout << "--- Resources ---\n";
        resources.printResourceList();

        std::cout << "\n--- Users ---\n";
        users.printUserList();

        std::cout << "\nDay 2 load complete. "
                  << resources.getAll().size() << " resources, "
                  << users.getAll().size()     << " users.\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << "\nFatal error: " << e.what() << '\n'
                  << "Check that the 'data/' folder exists next to the executable "
                     "and contains resources.txt and users.txt.\n";
        return 1;
    }

    return 0;
}