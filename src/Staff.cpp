// Staff.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Person subclass representing a staff member who can borrow up to 2 items.

#include "Staff.h"
#include <sstream>

Staff::Staff(int id, const std::string& name)
    : Person(id, name, 2) {} // Staff members can borrow up to 2 items, so we pass 2 as the borrow limit to the base Person constructor.
// The asString method provides a human-readable description of the staff member, including their ID, name, and current loan status (number of loans out of their borrow limit).

std::string Staff::asString() const {
    std::ostringstream oss;
    oss << "[STAFF]    " << _ID << " | " << _name
        << " (loans: " << _currentLoans << "/" << _borrow_limit << ")";
    return oss.str(); // The asString method provides a human-readable description of the staff member, including their ID, name, and current loan status (number of loans out of their borrow limit).
}