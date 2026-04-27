// LibStaff.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Person subclass representing a library staff member who cannot borrow items.

#include "LibStaff.h"
#include <sstream>

// Library staff can't borrow items, therefore their borrowing limit is 0.
LibStaff::LibStaff(int id, const std::string& name)
    : Person(id, name, 0) {}

std::string LibStaff::asString() const {
    std::ostringstream oss;
    oss << "[LIBSTAFF] " << _ID << " | " << _name << " (cannot borrow)";
    return oss.str();
}