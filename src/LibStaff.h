// =============================================================
// File:       LibStaff.h
// =============================================================
#pragma once
#include "Person.h"

/**
 * @class LibStaff
 * @brief Library staff; cannot borrow resources (limit = 0).
 */
class LibStaff final : public Person {
public:
    LibStaff(int id, const std::string& name);
    std::string asString() const override;
};