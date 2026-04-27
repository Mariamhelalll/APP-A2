// File:       Student.h
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Person subclass representing a student who can borrow up to 1 item.

#pragma once
#include "Person.h"

/**
 * @class Student
 * @brief Undergraduate/postgraduate user; borrow limit = 1.
 */
// The Student class represents a student user in the library system. 
//It is a concrete subclass of Person, with a borrowing limit of 1 item. The asString method provides a string representation of the student, including their ID, name, and current loan status (number of loans out of their borrow limit).
class Student final : public Person {
public:
    Student(int id, const std::string& name);
    std::string asString() const override;
};