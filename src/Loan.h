
// File:       Loan.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Represents a loan of a resource to a person, tracking the loan date and calculating due dates and overdue status.

#pragma once

#include <memory>
#include <string>
#include <chrono>
#include <iostream>
#include "Person.h"
#include "Resource.h"

/**
 * @class Loan
 * @brief One Person has borrowed one Resource at a specific time.
 *
 * Stores the loan timestamp using "std::chrono::system_clock", with a 14-day default loan period. isOverdue() compares the due dateto the current time and therefore enables the Day 7 overdue-detection feature.
 */
// The Loan class represents a loan of a resource to a person. It tracks the borrower, the resource, and the date of the loan. It provides methods to calculate the due date, check if the loan is overdue, and get a string representation of the loan for display purposes.
class Loan {
public:
    /// Default loan period in days. Resources become overdue this many days after they were borrowed.
    static constexpr int LOAN_PERIOD_DAYS = 14;

private:
    std::shared_ptr<Person>   _per;          ///< borrower
    std::shared_ptr<Resource> _res;          ///< borrowed item
    std::chrono::system_clock::time_point _loanDate;   ///< when borrowed

public:
    Loan(std::shared_ptr<Person> per, std::shared_ptr<Resource> res);

    std::shared_ptr<Person>   getPerson()   const { return _per; }
    std::shared_ptr<Resource> getResource() const { return _res; }
    std::chrono::system_clock::time_point getLoanDate() const { return _loanDate; }

    //Computing the due date ("loan date" + "LOAN_PERIOD_DAYS").
    std::chrono::system_clock::time_point getDueDate() const;

    // Checks if the current date/time is past the due date.
    bool isOverdue() const;

    //Days remaining until due (outputs negative if overdue).
    int daysUntilDue() const;

    //Formatted due date string (eg :"2026-05-08").
    std::string dueDateString() const;

    // Human-readable description (borrower + resource title).
    std::string asString() const;

    // Enables "std::cout << loan" to print the loan's string representation.
    friend std::ostream& operator<<(std::ostream& os, const Loan& loan) {
        return os << loan.asString();
    }
};