// =============================================================
// File:       ResourceList.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Owns the master list of Resources. Loads them from
//             a pipe-delimited text file using a factory pattern.
// =============================================================
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Resource.h"

class ResourceList {
private:
    std::vector<std::shared_ptr<Resource>> _r_list;

    // Factory helper: given a type token + parsed fields, build the
    // matching derived Resource. Returns nullptr if type is unknown.
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