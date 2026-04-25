// =============================================================
// File:       Loan.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Records a single borrowing transaction with a
//             timestamped loan date and a due date 14 days later.
//             Day 7 innovative feature: overdue detection.
// =============================================================
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
 * Stores the loan timestamp using std::chrono::system_clock, with
 * a 14-day default loan period. isOverdue() compares the due date
 * to the current time, enabling the Day 7 overdue-detection feature.
 */
class Loan {
public:
    /// Default loan period in days. Resources become overdue this
    /// many days after they were borrowed.
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

    /// Compute the due date (loan date + LOAN_PERIOD_DAYS).
    std::chrono::system_clock::time_point getDueDate() const;

    /// Day 7 innovative feature: is this loan past its due date?
    bool isOverdue() const;

    /// Days remaining until due (negative if overdue).
    int daysUntilDue() const;

    /// Formatted due date string, e.g. "2026-05-08".
    std::string dueDateString() const;

    /// Human-readable description (borrower + resource title).
    std::string asString() const;

    /// Stream-friendly output.
    friend std::ostream& operator<<(std::ostream& os, const Loan& loan) {
        return os << loan.asString();
    }
};