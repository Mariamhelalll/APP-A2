// File:       LibStaff.h
// Name:       Maryam Mohamed
// Student ID: 29073094         
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Person subclass representing a library staff member who cannot borrow items.

#pragma once
#include "Person.h"

/**
 * @class LibStaff
 * @brief Library staff (therefore cannot borrow resources (limit = 0) ).
 */
// The LibStaff class represents a library staff member, who is a type of Person. They have an ID and a name, but they cannot borrow resources (their borrow limit is 0). The asString method provides a string representation of the staff member.
class LibStaff final : public Person {
public:
    LibStaff(int id, const std::string& name);
    std::string asString() const override;
};