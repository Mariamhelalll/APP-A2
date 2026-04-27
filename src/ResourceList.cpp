// File:       ResourceList.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Implements the ResourceList class, which manages the collection of resources in the library.
// The ResourceList is responsible for loading resources from a file, creating the appropriate Resource objects based on the type specified in the file, and providing access to the list of resources for reporting and searching purposes.
// It includes a factory method for creating Resource objects from parsed data, and it handles errors in

#include "ResourceList.h"
#include "Book.h"
#include "Journal.h"
#include "Conference.h"
#include "StringUtils.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

// The following helper function generates a unique resource ID based on the number of resources loaded so far. 
// It formats the ID as "R" followed by a zero-padded number (eg: "R001", "R002"). This is used when loading resources from the file to ensure that each resource has a unique identifier.
namespace {
    std::string makeResourceID(std::size_t n) {
        std::ostringstream oss;
        oss << "R" << std::setw(3) << std::setfill('0') << n;
        return oss.str();
    }
}

// The makeResource function is a factory helper that takes a type token (eg: "BOOK", "JOURNAL", "CONFERENCE"), a resource ID, and a vector of parsed fields from the input file.
// It creates and returns a shared pointer to the appropriate Resource subclass based on the type token. 
// If the type is unknown or if there are not enough fields to construct the resource, it returns nullptr. This function is used by the ResourceList constructor when loading resources from the file to create the correct Resource objects based on the data provided.
std::shared_ptr<Resource> ResourceList::makeResource(
    const std::string& type,
    const std::string& id,
    const std::vector<std::string>& fields)
{
    if (fields.size() < 2) {
        return nullptr;
    }

    if (type == "BOOK") {
        return std::make_shared<Book>(id, fields[0], fields[1]);
    }
    if (type == "JOURNAL") {
        return std::make_shared<Journal>(id, fields[0], fields[1]);
    }
    if (type == "CONFERENCE") {
        return std::make_shared<Conference>(id, fields[0], fields[1]);
    }
    return nullptr;
}

// The constructor for ResourceList takes a filename as input and attempts to load resources from the specified file.
// It reads the file line by line, skipping empty lines and comments (lines starting with '#'). 
//For each valid line, it splits the line into tokens using the pipe '|' delimiter, extracts the type and fields, and uses the makeResource factory function to create the appropriate Resource object. 
//If the file cannot be opened, or if there are malformed lines or unknown types, it throws a runtime error
ResourceList::ResourceList(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error(
            "ResourceList: could not open file '" + filename + "'");
    }

    std::string line;
    std::size_t lineNo = 0;
    std::size_t nextId = 1;

    while (std::getline(in, line)) {
        ++lineNo;
        if (line.empty() || line.front() == '#') continue;

        // Use the shared split helper from StringUtils (Day 6 DRY fix).
        auto tokens = StringUtils::split(line, '|');
        if (tokens.size() < 3) {
            std::cerr << "[warn] resources.txt line " << lineNo
                      << ": skipping malformed line\n";
            continue;
        }

        const std::string& type = tokens[0];
        std::vector<std::string> fields(tokens.begin() + 1, tokens.end());

        auto resource = makeResource(type, makeResourceID(nextId), fields);
        if (!resource) {
            std::cerr << "[warn] resources.txt line " << lineNo
                      << ": unknown type '" << type << "'\n";
            continue;
        }

        _r_list.push_back(std::move(resource));
        ++nextId;
    }
}
// The printResourceList function iterates through the list of resources and prints each one to the console using the overloaded operator<<, which calls the asString method of each Resource to get its string representation. 
// This allows for polymorphic behavior, as the correct asString implementation will be called for each derived Resource type (Book, Journal, Conference).
void ResourceList::printResourceList() const {
    for (const auto& r : _r_list) {
        std::cout << *r << '\n';
    }
}