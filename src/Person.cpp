// Person.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

#include "Person.h"
// The Person class represents a person who can borrow resources from the library.
// It has an ID, a name, a borrowing limit, and tracks the number of current loans. 
// The constructor initialises these values, and the asString method provides a string representation of the person for display purposes.
Person::Person(int id, const std::string& name, int borrowLimit)
    : _borrow_limit(borrowLimit), _ID(id), _name(name), _currentLoans(0) {}