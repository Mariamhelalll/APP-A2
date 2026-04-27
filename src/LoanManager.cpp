
// File:       LoanManager.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Manages the borrowing and returning of resources, enforcing all business rules and maintaining an activity log.

#include "LoanManager.h"
#include "Exceptions.h"

#include <algorithm> // Required for std::find_if
#include <chrono>    // Required for system_clock and time manipulation
#include <ctime>     // Required for std::tm and time_t
#include <iomanip>   // Required for std::put_time (formatting output)
#include <sstream>   // Required for std::ostringstream


// formats the current time as "YYYY-MM-DD HH:MM:SS" for activity-log entries.

namespace {
    std::string timestamp() {
        const auto now = std::chrono::system_clock::now();
        const auto tt  = std::chrono::system_clock::to_time_t(now);
        std::tm tm{};
    #ifdef _WIN32
        localtime_s(&tm, &tt);
    #else
        localtime_r(&tt, &tm);
    #endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
}


LoanManager::LoanManager(ResourceList& resources, UserList& users)
    : _resources(resources), _users(users) {}

// ------------------------------------------------------------------
// Lookup helpers using std::find_if with lambdas.
// ------------------------------------------------------------------
std::shared_ptr<Person> LoanManager::findUser(int userID) const {
    const auto& users = _users.getAll();
    auto it = std::find_if(users.begin(), users.end(),
        [userID](const std::shared_ptr<Person>& p) {
            return p->getID() == userID;
        });
    if (it == users.end()) {
        throw NotFoundException(
            "User with ID " + std::to_string(userID) + " does not exist.");
    }
    return *it;
}

std::shared_ptr<Resource> LoanManager::findResource(const std::string& resourceID) const {
    const auto& resources = _resources.getAll();
    auto it = std::find_if(resources.begin(), resources.end(),
        [&resourceID](const std::shared_ptr<Resource>& r) {
            return r->getID() == resourceID;
        });
    if (it == resources.end()) {
        throw NotFoundException(
            "Resource with ID '" + resourceID + "' does not exist.");
    }
    return *it;
}

void LoanManager::logEvent(const std::string& message) {
    _activityLog.push_back("[" + timestamp() + "] " + message);
}

// ------------------------------------------------------------------
// The borrow operation: every business rule enforced here.
// Throws a specific exception for each kind of failure.
// ------------------------------------------------------------------
void LoanManager::borrow(int userID, const std::string& resourceID) {
    auto user     = findUser(userID);         // throws NotFoundException
    auto resource = findResource(resourceID); // throws NotFoundException

    // Rule: Conferences cannot be borrowed at all.
    if (!resource->canLend()) {
        throw ResourceUnavailableException(
            "Resource '" + resource->getTitle() +
            "' is reference-only and cannot be borrowed.");
    }

    // Rule: each Book/Journal can only be on loan once at a time.
    if (resource->isBorrowed()) {
        throw ResourceUnavailableException(
            "Resource '" + resource->getTitle() +
            "' is already on loan.");
    }

    // Rule: enforce the user's borrow limit.
    //   Student -> 1, Staff -> 2, LibStaff -> 0.
    if (!user->canBorrowMore()) {
        throw BorrowLimitException(
            user->getName() + " has reached their borrow limit (" +
            std::to_string(user->getCurrentLoans()) + "/" +
            std::to_string(user->getBorrowLimit()) + ").");
    }

    // All checks passed -- commit the loan.
    resource->setBorrowed(true);
    user->incrementLoans();
    _activeLoans.emplace_back(user, resource);

    logEvent("BORROW  - " + user->getName() + " borrowed '" +
             resource->getTitle() + "' (" + resource->getID() + ")");
}

// ------------------------------------------------------------------
// The return operation: find the matching loan, reverse it.
// ------------------------------------------------------------------
void LoanManager::returnResource(int userID, const std::string& resourceID) {
    // Validate both IDs exist (for a clean error message).
    auto user     = findUser(userID);
    auto resource = findResource(resourceID);

    // Find the matching active loan.
    auto it = std::find_if(_activeLoans.begin(), _activeLoans.end(),
        [userID, &resourceID](const Loan& loan) {
            return loan.getPerson()->getID()   == userID &&
                   loan.getResource()->getID() == resourceID;
        });

    if (it == _activeLoans.end()) {
        throw NotFoundException(
            "No active loan exists for user " + std::to_string(userID) +
            " and resource '" + resourceID + "'.");
    }

    // Reverse the loan.
    resource->setBorrowed(false);
    user->decrementLoans();
    _activeLoans.erase(it);

    logEvent("RETURN  - " + user->getName() + " returned '" +
             resource->getTitle() + "' (" + resource->getID() + ")");
}