// File:       Student.h
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

#pragma once
#include "Person.h"

/**
 * @class Student
 * @brief Undergraduate/postgraduate user; borrow limit = 1.
 *
 * Marked `final` — no class should inherit from a concrete leaf
 * type. If you need a sub-type of student later, inherit from
 * Person instead.
 */
class Student final : public Person {
public:
    Student(int id, const std::string& name);
    std::string asString() const override;
};