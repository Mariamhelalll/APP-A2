// LibStaff.h
#pragma once
#include "Person.h"

class LibStaff : public Person {
public:
    LibStaff(int id, const std::string& name);
    std::string asString() const override;
};