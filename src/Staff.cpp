// Staff.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

#include "Staff.h"
#include <sstream>

Staff::Staff(int id, const std::string& name)
    : Person(id, name, 2) {}

std::string Staff::asString() const {
    std::ostringstream oss;
    oss << "[STAFF]    " << _ID << " | " << _name
        << " (loans: " << _currentLoans << "/" << _borrow_limit << ")";
    return oss.str();
}