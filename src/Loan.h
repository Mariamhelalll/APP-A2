// =============================================================
// File:       Loan.h
// Author:     Maryam Mohamed 
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Records a single borrowing transaction: one Person
//             has borrowed one Resource. Uses shared_ptr so the
//             Loan does not exclusively own either object.
// =============================================================
#pragma once

#include <memory>
#include <string>
#include "Person.h"
#include "Resource.h"

class Loan {
private:
    std::shared_ptr<Person>   _per;
    std::shared_ptr<Resource> _res;

public:
    Loan(std::shared_ptr<Person> per, std::shared_ptr<Resource> res);

    std::shared_ptr<Person>   getPerson()   const { return _per; }
    std::shared_ptr<Resource> getResource() const { return _res; }

    // Polymorphic description of the loan (borrower + resource title).
    std::string asString() const;
};