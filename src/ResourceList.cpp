// =============================================================
// File:       ResourceList.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// =============================================================
#include "ResourceList.h"
#include "Book.h"
#include "Journal.h"
#include "Conference.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>

// ------------------------------------------------------------------
// Small helper: split a line on the '|' delimiter into its tokens.
// Kept in an anonymous namespace so it is private to this file.
// ------------------------------------------------------------------
namespace {
    std::vector<std::string> split(const std::string& line, char delim) {
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    // Produces "R001", "R002", ... from a counter.
    // Uses stream manipulators for zero-padding (contemporary C++).
    std::string makeResourceID(std::size_t n) {
        std::ostringstream oss;
        oss << "R" << std::setw(3) << std::setfill('0') << n;
        return oss.str();
    }
}

// ------------------------------------------------------------------
// Factory: one place where the type string becomes a concrete
// derived object. Adding a new Resource type = one new branch here.
// ------------------------------------------------------------------
std::shared_ptr<Resource> ResourceList::makeResource(
    const std::string& type,
    const std::string& id,
    const std::vector<std::string>& fields)
{
    // fields layout:
    //   BOOK       -> [title, author]
    //   JOURNAL    -> [title, issn]
    //   CONFERENCE -> [title, acronym]
    if (fields.size() < 2) {
        return nullptr;  // malformed line -- caller will skip
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
    return nullptr;  // unknown type token
}

// ------------------------------------------------------------------
// Constructor: open the file, parse each line, build the list.
// ------------------------------------------------------------------
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

        // Skip blank lines and full-line comments (start with '#').
        if (line.empty() || line.front() == '#') continue;

        auto tokens = split(line, '|');
        if (tokens.size() < 3) {
            std::cerr << "[warn] resources.txt line " << lineNo
                      << ": skipping malformed line\n";
            continue;
        }

        // First token = type; remaining tokens = per-type fields.
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

void ResourceList::printResourceList() const {
    for (const auto& r : _r_list) {
        std::cout << *r << '\n';
    }
}