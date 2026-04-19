// Person.h
#pragma once

#include <string>
#include <iostream>

class Person {
protected:
    int         _borrow_limit;    // 1 for Student, 2 for Staff, 0 for LibStaff
    int         _ID;              // unique integer ID
    std::string _name;
    int         _currentLoans;    // tracks how many items the person currently has

public:
    Person(int id, const std::string& name, int borrowLimit);
    virtual ~Person() = default;

    virtual std::string asString() const = 0;

    // Accessors
    int         getID()          const { return _ID; }
    const std::string& getName() const { return _name; }
    int         getBorrowLimit() const { return _borrow_limit; }
    int         getCurrentLoans() const { return _currentLoans; }

    // Mutators used by borrow/return flow (Day 3)
    void incrementLoans() { ++_currentLoans; }
    void decrementLoans() { if (_currentLoans > 0) --_currentLoans; }

    // Helper — used in the borrow check on Day 3
    bool canBorrowMore() const { return _currentLoans < _borrow_limit; }

    // Operator overloads
    bool operator==(const Person& other) const { return _ID == other._ID; }

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << p.asString();
    }
};