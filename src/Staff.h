// =============================================================
// File:       Staff.h
// =============================================================
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