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
#include <iostream>
#include "Person.h"
#include "Resource.h"

/**
 * @class Loan
 * @brief One Person has borrowed one Resource.
 *
 * Holds shared_ptrs so the Loan participates in shared ownership
 * with ResourceList / UserList. Value-type: copied freely, stored
 * in std::vector by value in LoanManager.
 */
class Loan {
private:
    std::shared_ptr<Person>   _per;   ///< borrower
    std::shared_ptr<Resource> _res;   ///< borrowed item

public:
    Loan(std::shared_ptr<Person> per, std::shared_ptr<Resource> res);

    std::shared_ptr<Person>   getPerson()   const { return _per; }
    std::shared_ptr<Resource> getResource() const { return _res; }

    /// Human-readable description (borrower + resource title).
    std::string asString() const;

    /// Stream-friendly output, consistent with Resource and Person.
    friend std::ostream& operator<<(std::ostream& os, const Loan& loan) {
        return os << loan.asString();
    }
};