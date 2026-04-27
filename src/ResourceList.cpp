// File:       ResourceList.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

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

// ------------------------------------------------------------------
// File-local helper: format a counter as "R001", "R002", ... using
// stream manipulators for zero-padding.
// ------------------------------------------------------------------
namespace {
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

void ResourceList::printResourceList() const {
    for (const auto& r : _r_list) {
        std::cout << *r << '\n';
    }
}