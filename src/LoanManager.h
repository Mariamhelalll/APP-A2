
// File:       LoanManager.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Central controller for borrow / return operations.
//             Enforces every business rule from the brief:
//               - Students borrow at most 1, Staff at most 2,
//                 LibStaff cannot borrow.
//               - Each Book/Journal can be loaned once at a time.
//               - Conferences cannot be borrowed.
//             Also maintains an ordered activity log of every
//             borrow / return event.

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Loan.h"
#include "ResourceList.h"
#include "UserList.h"

/**
 * @class LoanManager
 * @brief Orchestrates borrow/return against the two catalogues.
 *
 * Holds references (not copies) to ResourceList and UserList so
 * that a single in-memory state is shared with the rest of the
 * program. Violations of business rules throw typed exceptions
 * from the LibraryException hierarchy (see Exceptions.h).
 */
class LoanManager {
private:
    ResourceList& _resources;                  ///< catalogue of items
    UserList&     _users;                      ///< catalogue of users

    std::vector<Loan>        _activeLoans;     ///< outstanding loans
    std::vector<std::string> _activityLog;     ///< ordered event log

    /// Look up a user by ID, or throw NotFoundException.
    std::shared_ptr<Person>   findUser(int userID) const;

    /// Look up a resource by ID, or throw NotFoundException.
    std::shared_ptr<Resource> findResource(const std::string& resourceID) const;

    /// Append a timestamped entry to the activity log.
    void logEvent(const std::string& message);

public:
    LoanManager(ResourceList& resources, UserList& users);

    /// Attempt to borrow. Throws on any business-rule violation.
    void borrow(int userID, const std::string& resourceID);

    /// Return a previously-borrowed resource. Throws if the loan
    /// does not exist.
    void returnResource(int userID, const std::string& resourceID);

    const std::vector<Loan>&        getActiveLoans() const { return _activeLoans; }
    const std::vector<std::string>& getActivityLog() const { return _activityLog; }
};