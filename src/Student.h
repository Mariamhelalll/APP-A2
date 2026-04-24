// =============================================================
// File:       Student.h
// =============================================================
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