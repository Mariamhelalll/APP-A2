// File:       Book.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Concrete Resource subclass representing a lendable book item.

#pragma once
#include "Resource.h"


class Book final : public Resource {
private:
    std::string _author;

public:
    Book(const std::string& id, const std::string& title, const std::string& author);
    std::string asString() const override;
    const std::string& getAuthor() const { return _author; }
};