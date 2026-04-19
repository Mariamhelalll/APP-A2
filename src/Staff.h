// Staff.h
#pragma once
#include "Person.h"

class Staff : public Person {
public:
    Staff(int id, const std::string& name);
    std::string asString() const override;
};