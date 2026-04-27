// File:       ResourceList.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    - Declares the ResourceList class, which manages the collection of resources in the library. 
//             - It includes a constructor that loads resources from a file and a method to print the list of resources. 
//             - The ResourceList also provides read-only access to the list of resources for reporting and searching purposes.

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Resource.h"
// The ResourceList class manages the collection of resources in the library.
// It is responsible for loading resources from a file, creating the appropriate Resource objects based on the type specified in the file, and providing access to the list of resources for reporting and searching purposes.
//   The class includes a factory method for creating Resource objects from parsed data, and it handles errors in the input file by throwing exceptions.
class ResourceList {
private:
    std::vector<std::shared_ptr<Resource>> _r_list;

    // Factory: one place where the type string becomes a concrete derived object. Adding a new Resource type = one new branch here.
    static std::shared_ptr<Resource> makeResource(
        const std::string& type,
        const std::string& id,
        const std::vector<std::string>& fields);

public:
    // Loads resources from a pipe-delimited text file.
    // Throws std::runtime_error if the file cannot be opened.
    explicit ResourceList(const std::string& filename);

    // Prints every resource polymorphically via operator<<.
    void printResourceList() const;

    // Read-only access for reports, searches, and loan lookup.
    const std::vector<std::shared_ptr<Resource>>& getAll() const { return _r_list; }
};