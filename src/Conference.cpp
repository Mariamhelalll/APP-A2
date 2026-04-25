// Conference.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
#include "Conference.h"
#include <sstream>

// Conferences cannot be lent  (therefore we will pass false to Resource constructor)
Conference::Conference(const std::string& id, const std::string& title, const std::string& acronym)
    : Resource(id, title, false), _acronym(acronym) {}

std::string Conference::asString() const {
    std::ostringstream oss;
    oss << "[CONF]    " << _ID << " | " << _title << " (" << _acronym << ") — reference only";
    return oss.str();
}