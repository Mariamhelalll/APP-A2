
// File:       Loan.cpp
// Name:       Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

#include "Loan.h"

#include <ctime>
#include <iomanip>
#include <sstream>

Loan::Loan(std::shared_ptr<Person> per, std::shared_ptr<Resource> res)
    : _per(std::move(per)),
      _res(std::move(res)),
      _loanDate(std::chrono::system_clock::now()) {}

std::chrono::system_clock::time_point Loan::getDueDate() const {
    return _loanDate + std::chrono::hours(24 * LOAN_PERIOD_DAYS);
}

bool Loan::isOverdue() const {
    return std::chrono::system_clock::now() > getDueDate();
}

int Loan::daysUntilDue() const {
    const auto now  = std::chrono::system_clock::now();
    const auto diff = getDueDate() - now;
    return static_cast<int>(
        std::chrono::duration_cast<std::chrono::hours>(diff).count() / 24);
}

std::string Loan::dueDateString() const {
    const auto due_tt = std::chrono::system_clock::to_time_t(getDueDate());
    std::tm tm{};
#ifdef _WIN32
    localtime_s(&tm, &due_tt);
#else
    localtime_r(&due_tt, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

std::string Loan::asString() const {
    std::ostringstream oss;
    oss << _per->getName() << " has borrowed '" << _res->getTitle()
        << "' (" << _res->getID() << "), due " << dueDateString();
    if (isOverdue()) {
        oss << " *** OVERDUE ***";
    }
    return oss.str();
}