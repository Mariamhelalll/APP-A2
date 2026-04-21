// =============================================================
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
//             borrow / return event (needed for Day 5).
// =============================================================
#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Loan.h"
#include "ResourceList.h"
#include "UserList.h"

class LoanManager {
private:
    // The two catalogues the manager operates on. Held as
    // references because the lists live in main() and must
    // outlive the manager.
    ResourceList& _resources;
    UserList&     _users;

    // Current outstanding loans.
    std::vector<Loan> _activeLoans;

    // Ordered history of every borrow / return event as a string.
    // Displayed on request by the extended activity-log feature.
    std::vector<std::string> _activityLog;

    // --- Private helpers -----------------------------------------
    // Look up a user by ID. Throws NotFoundException if absent.
    std::shared_ptr<Person> findUser(int userID) const;

    // Look up a resource by ID. Throws NotFoundException if absent.
    std::shared_ptr<Resource> findResource(const std::string& resourceID) const;

    // Append a single line to the activity log with a timestamp.
    void logEvent(const std::string& message);

public:
    // Constructor takes references to both catalogues.
    LoanManager(ResourceList& resources, UserList& users);

    // Attempt to borrow. Throws on any business-rule violation.
    void borrow(int userID, const std::string& resourceID);

    // Attempt to return. Throws if the loan does not exist.
    void returnResource(int userID, const std::string& resourceID);

    // Read-only access for Day 4 reports.
    const std::vector<Loan>&        getActiveLoans()  const { return _activeLoans; }
    const std::vector<std::string>& getActivityLog() const { return _activityLog; }
};