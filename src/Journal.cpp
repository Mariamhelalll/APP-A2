// Journal.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Resource subclass representing a lendable journal item.
#include "Journal.h"
#include <sstream>

// As mentioned in the brief, journals can be lent.
Journal::Journal(const std::string& id, const std::string& title, const std::string& issn)
    : Resource(id, title, true), _issn(issn) {}
// The asString method provides a human-readable description of the journal, including its ID, title, and ISSN. It also indicates whether the journal is currently on loan or available.
std::string Journal::asString() const {
    std::ostringstream oss;
    oss << "[JOURNAL] " << _ID << " | " << _title << " (ISSN " << _issn << ")"
        << (_isBorrowed ? " (on loan)" : " (available)");
    return oss.str();
}