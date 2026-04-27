// File:       Conference.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Resource subclass representing a reference-only conference item.

#pragma once
#include "Resource.h"


class Conference final : public Resource {
private:
    std::string _acronym;   /// (eg: "OOPSLA", "ICSE")

public:
    Conference(const std::string& id, const std::string& title, const std::string& acronym);
    std::string asString() const override;
    const std::string& getAcronym() const { return _acronym; }
};