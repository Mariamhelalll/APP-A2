
// File:       Staff.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

#pragma once
#include "Person.h"

/**
 * @class Staff
 * @brief Academic or administrative staff; borrow limit = 2.
 */
class Staff final : public Person {
public:
    Staff(int id, const std::string& name);
    std::string asString() const override;
};