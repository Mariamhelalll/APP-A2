// Student.cpp
// Author:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Person subclass representing a student who can borrow up to 1 item.
#include "Student.h"
#include <sstream>

// Students can borrow 1 item, so we pass 1 as the borrow limit to the base Person constructor.
Student::Student(int id, const std::string& name)
    : Person(id, name, 1) {}
// The asString method provides a human-readable description of the student, including their ID, name, and current loan status (number of loans out of their borrow limit).
std::string Student::asString() const {
    std::ostringstream oss;
    oss << "[STUDENT]  " << _ID << " | " << _name
        << " (loans: " << _currentLoans << "/" << _borrow_limit << ")";
    return oss.str();
}