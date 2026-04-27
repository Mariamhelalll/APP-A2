
// File:       LoanManager.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:  - Manages the borrowing and returning of resources, enforcing all business rules and maintaining an activity log.
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
 * The LoanManager is responsible for enforcing all the business rules around borrowing and returning resources. It maintains a list of active loans and an activity log of all transactions. It uses the ResourceList and UserList to validate IDs and retrieve the corresponding objects during borrow/return operations. The methods throw specific exceptions for different kinds of rule violations, allowing the caller to handle errors gracefully.
 */
class LoanManager {
private:
    ResourceList& _resources;                  //< catalogue of items
    UserList&     _users;                      //< catalogue of users

    std::vector<Loan>        _activeLoans;     //< outstanding loans
    std::vector<std::string> _activityLog;     //< ordered event log

    // Look up a user by ID, or throw NotFoundException.
    std::shared_ptr<Person>   findUser(int userID) const;

    // Look up a resource by ID, or throw NotFoundException.
    std::shared_ptr<Resource> findResource(const std::string& resourceID) const;

    // Append a timestamped entry to the activity log.
    void logEvent(const std::string& message);

public:
    LoanManager(ResourceList& resources, UserList& users); // Constructor takes references to the resource and user lists, which it uses for lookups during borrow/return operations. It does not take ownership of these lists, as they are managed elsewhere in the program.

    // Attempt to borrow + throws on any business-rule violation.
    void borrow(int userID, const std::string& resourceID);

    // Return a previously-borrowed resource + throws if the loan doesn't exist.
    void returnResource(int userID, const std::string& resourceID);

    const std::vector<Loan>&        getActiveLoans() const { return _activeLoans; } // Read-only access to the list of active loans, used for generating reports and checking loan status.
    const std::vector<std::string>& getActivityLog() const { return _activityLog; } // Read-only access to the activity log, which contains timestamped entries of all borrow and return transactions for auditing and reporting purposes.
};