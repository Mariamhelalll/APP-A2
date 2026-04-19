// Journal.cpp
#include "Journal.h"
#include <sstream>

// Journals can be lent.
Journal::Journal(const std::string& id, const std::string& title, const std::string& issn)
    : Resource(id, title, true), _issn(issn) {}

std::string Journal::asString() const {
    std::ostringstream oss;
    oss << "[JOURNAL] " << _ID << " | " << _title << " (ISSN " << _issn << ")"
        << (_isBorrowed ? " (on loan)" : " (available)");
    return oss.str();
}