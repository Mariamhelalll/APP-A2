// Student.h
#pragma once

#include "Person.h"

class Student : public Person {
public:
    Student(int id, const std::string& name);
    std::string asString() const override;
};