
// File:       Staff.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Person subclass representing a staff member who can borrow up to 2 items.

#pragma once
#include "Person.h"

/**
 * @class Staff
 * @brief Academic or administrative staff; borrow limit = 2.
 */
// The Staff class represents a staff member in the library system. It is a concrete subclass of Person, with a borrowing limit of 2 items. 
//The asString method provides a string representation of the staff member, including their ID, name, and current loan status (number of loans out of their borrow limit).
 
class Staff final : public Person {
public:
    Staff(int id, const std::string& name);
    std::string asString() const override; 
};