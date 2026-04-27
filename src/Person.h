// File:       Person.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:   - Abstract base class for library users.
//            - Derived classes (Student, Staff, LibStaff) set their own borrow limit via the base constructor.
//            - Person cannot be instantiated directly because asString() is pure virtual.

#pragma once

#include <string>
#include <iostream>

/**
 * @class Person
 * @brief Abstract base class for library users.
 */
class Person {
protected:
    int         _borrow_limit;   ///< max concurrent loans (0/1/2)
    int         _ID;             ///< unique integer ID
    std::string _name;           ///< full name
    int         _currentLoans;   ///< count of outstanding loans
// The Person class represents a person who can borrow resources from the library. 
// It has an ID, a name, a borrowing limit, and tracks the number of current loans. 
//The constructor initialises these values, and the asString method provides a string representation of the person for display purposes.
public:
    Person(int id, const std::string& name, int borrowLimit);

    virtual ~Person() = default;

    virtual std::string asString() const = 0;

    int                 getID()           const { return _ID; } // The getID method returns the unique integer ID of the person, which is used for identification and lookup purposes in the system.
    const std::string&  getName()         const { return _name; } // The getName method returns the full name of the person, which is used for display purposes in reports and listings.
    int                 getBorrowLimit()  const { return _borrow_limit; } //  The getBorrowLimit method returns the maximum number of concurrent loans allowed for this person, which is determined by their type (Student, Staff, LibStaff) and is used to enforce borrowing rules in the LoanManager.
    int                 getCurrentLoans() const { return _currentLoans; } // The getCurrentLoans method returns the current number of outstanding loans for this person, which is tracked by the LoanManager when they borrow or return resources. This is used to check if they can borrow more items based on their borrow limit.

    void incrementLoans()       { ++_currentLoans; }
    void decrementLoans()       { if (_currentLoans > 0) --_currentLoans; }

    bool canBorrowMore() const  { return _currentLoans < _borrow_limit; }

    bool operator==(const Person& other) const { return _ID == other._ID; }

    // Alphabetical ordering by name — enables sorting users in reports.
    bool operator<(const Person& other)  const { return _name < other._name; }
    // Enables "std::cout << person" to print the person's string representation.
    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << p.asString();
    }
};