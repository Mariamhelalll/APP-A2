
// File:       Loan.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Represents a loan of a resource to a person, tracking the loan date and calculating due dates and overdue status.

#include "Loan.h"

#include <ctime>
#include <iomanip>
#include <sstream>

Loan::Loan(std::shared_ptr<Person> per, std::shared_ptr<Resource> res)
    : _per(std::move(per)), // Take ownership of the resource and person via shared_ptr, so we move them into our members.
      _res(std::move(res)), // The loan date is set to the current time when the loan is created.
      _loanDate(std::chrono::system_clock::now()) {} // The constructor initialises the loan with the borrower, the resource, and sets the loan date to now.

std::chrono::system_clock::time_point Loan::getDueDate() const {
    return _loanDate + std::chrono::hours(24 * LOAN_PERIOD_DAYS); // Due date is calculated by adding the loan period (in days) to the loan date.
}

bool Loan::isOverdue() const {
    return std::chrono::system_clock::now() > getDueDate(); // A loan is overdue if the current time is past the due date.
}

int Loan::daysUntilDue() const {
    const auto now  = std::chrono::system_clock::now();// Get the current time to compare against the due date.
    const auto diff = getDueDate() - now; // Calculate the difference between the due date and now. This will be positive if not overdue, negative if overdue.
    return static_cast<int>(
        std::chrono::duration_cast<std::chrono::hours>(diff).count() / 24); // Convert the difference from hours to days and return it as an integer. Negative if overdue, positive if not.
}

std::string Loan::dueDateString() const {
    const auto due_tt = std::chrono::system_clock::to_time_t(getDueDate());// Convert the due date to a time_t for formatting. We need to convert the time_point to time_t to format it as a string.
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &due_tt); // Windows uses localtime_s for thread-safe local time conversion, while POSIX systems use localtime_r.  Both cases are handeled for portability.
#else
    localtime_r(&due_tt, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}
// The asString method provides a human-readable description of the loan, including the borrower's name, the resource title and ID, the due date, and an overdue warning if applicable. It uses string streams to format the output neatly.
std::string Loan::asString() const {
    std::ostringstream oss;
    oss << _per->getName() << " has borrowed '" << _res->getTitle()
        << "' (" << _res->getID() << "), due " << dueDateString();
    if (isOverdue()) {
        oss << " *** OVERDUE ***";
    }
    return oss.str();
}