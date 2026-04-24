// =============================================================
// File:       Person.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Abstract base class for every system user (Student,
//             Staff, LibStaff). Carries the identity, borrow-limit
//             policy, and current-loan count used by the business
//             rules in LoanManager.
// =============================================================
#pragma once

#include <string>
#include <iostream>

/**
 * @class Person
 * @brief Abstract base class for library users.
 *
 * Derived classes (Student, Staff, LibStaff) set their own borrow
 * limit via the base constructor. Person cannot be instantiated
 * directly because asString() is pure virtual.
 */
class Person {
protected:
    int         _borrow_limit;   ///< max concurrent loans (0/1/2)
    int         _ID;             ///< unique integer ID
    std::string _name;           ///< full name
    int         _currentLoans;   ///< count of outstanding loans

public:
    Person(int id, const std::string& name, int borrowLimit);

    virtual ~Person() = default;

    virtual std::string asString() const = 0;

    int                 getID()           const { return _ID; }
    const std::string&  getName()         const { return _name; }
    int                 getBorrowLimit()  const { return _borrow_limit; }
    int                 getCurrentLoans() const { return _currentLoans; }

    void incrementLoans()       { ++_currentLoans; }
    void decrementLoans()       { if (_currentLoans > 0) --_currentLoans; }

    bool canBorrowMore() const  { return _currentLoans < _borrow_limit; }

    bool operator==(const Person& other) const { return _ID == other._ID; }

    /// Alphabetical ordering by name — enables sorting users in reports.
    bool operator<(const Person& other)  const { return _name < other._name; }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << p.asString();
    }
};