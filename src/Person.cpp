// Person.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

#include "Person.h"

Person::Person(int id, const std::string& name, int borrowLimit)
    : _borrow_limit(borrowLimit), _ID(id), _name(name), _currentLoans(0) {}