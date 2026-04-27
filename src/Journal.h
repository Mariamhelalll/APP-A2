
// File:       Journal.h
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Resource subclass representing a lendable journal item.

#pragma once
#include "Resource.h"

/**
 * @class Journal
 * @brief A lendable periodical identified by its ISSN.
 */
// The Journal class represents a lendable journal resource in the library. It has an ID, a title, and an ISSN. The asString method provides a string representation of the journal, including its ID, title, and ISSN. The getISSN method allows retrieval of the journal's ISSN.
class Journal final : public Resource {
private:
    std::string _issn;   ///< International Standard Serial Number

public:
    Journal(const std::string& id, const std::string& title, const std::string& issn);
    std::string asString() const override;
    const std::string& getISSN() const { return _issn; }
};