// Student.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
#include "Student.h"
#include <sstream>

// Students can borrow a maximum of 1 resource — hardcoded in the constructor.
Student::Student(int id, const std::string& name)
    : Person(id, name, 1) {}

std::string Student::asString() const {
    std::ostringstream oss;
    oss << "[STUDENT]  " << _ID << " | " << _name
        << " (loans: " << _currentLoans << "/" << _borrow_limit << ")";
    return oss.str();
}