// =============================================================
// File:       <Resource.h>
// Author:     <Maryam Mohamed>
// Student ID: <29073094>
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 — Library Management System
// Purpose:    <one-line description>
// =============================================================
// Resource.h
#pragma once

#include <string>
#include <iostream>

class Resource {
protected:
    bool        _canLend;      // false for Conference, true for Book/Journal
    std::string _ID;           // unique string ID, e.g. "R001"
    bool        _isBorrowed;   // true when currently on loan
    std::string _title;

public:
    // Constructor: sets ID, title, and whether this type can be lent.
    // _isBorrowed defaults to false at creation.
    Resource(const std::string& id, const std::string& title, bool canLend);

    // Virtual destructor (required for safe polymorphic deletion.)
    virtual ~Resource() = default;

    // Pure virtual (each derived class must describe itself).
    // Making this pure virtual forces Resource to be abstract.
    virtual std::string asString() const = 0;

    // Accessors (const-correct)
    const std::string& getID()    const { return _ID; }
    const std::string& getTitle() const { return _title; }
    bool canLend()     const { return _canLend; }
    bool isBorrowed()  const { return _isBorrowed; }

    // Mutators used by the borrow/return flow (implemented Day 3)
    void setBorrowed(bool state) { _isBorrowed = state; }

    // Operator overloads — covered in the 1st++ band criteria
    bool operator<(const Resource& other)  const { return _title < other._title; }
    bool operator==(const Resource& other) const { return _ID == other._ID; }

    // Polymorphic stream output (delegates to asString())
    friend std::ostream& operator<<(std::ostream& os, const Resource& r) {
        return os << r.asString();
    }
};