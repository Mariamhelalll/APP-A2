// Book.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Resource subclass representing a lendable book item.
#include "Book.h"
#include <sstream>

// Books can be lent = (this will pass true to "Resource" constructor)
Book::Book(const std::string& id, const std::string& title, const std::string& author)
    : Resource(id, title, true), _author(author) {}

std::string Book::asString() const {
    std::ostringstream oss;
    oss << "[BOOK]    " << _ID << " | " << _title << " by " << _author
        << (_isBorrowed ? " (on loan)" : " (available)");
    return oss.str();
}