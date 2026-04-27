
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
// This is used in the logEvent method to timestamp each borrow/return action in the activity log.
namespace {
    std::string timestamp() {
        const auto now = std::chrono::system_clock::now(); // Get the current time as a time_point.
        const auto tt  = std::chrono::system_clock::to_time_t(now); // Convert the time_point to time_t, which is a more traditional C-style time representation that can be formatted.
        std::tm tm{};
    #ifdef _WIN32 // Windows uses localtime_s for thread-safe local time conversion, while POSIX systems use localtime_r.  Both cases are handeled for portability.
        localtime_s(&tm, &tt);
    #else
        localtime_r(&tt, &tm);
    #endif
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
}

// The constructor takes references to the resource and user lists, which it uses for lookups during borrow/return operations. It does not take ownership of these lists, as they are managed elsewhere in the program.
LoanManager::LoanManager(ResourceList& resources, UserList& users)
    : _resources(resources), _users(users) {}


// Look up a user by ID, or throw NotFoundException if the user does not exist. 
//This is a helper method used by both borrow and return operations to validate the user ID and retrieve the corresponding Person object.
std::shared_ptr<Person> LoanManager::findUser(int userID) const {
    const auto& users = _users.getAll(); // Get the list of users from the UserList. We will search through this list to find the user with the matching ID.
    auto it = std::find_if(users.begin(), users.end(), //
        [userID](const std::shared_ptr<Person>& p) {
            return p->getID() == userID;
        });
    if (it == users.end()) {
        throw NotFoundException(
            "User with ID " + std::to_string(userID) + " does not exist.");
    }
    return *it;
}
// Look up a resource by ID, or throw NotFoundException if the resource does not exist.
// This is a helper method used by both borrow and return operations to validate the resource ID and retrieve the corresponding Resource object.
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
// Append a timestamped entry to the activity log. 
// This is called after every successful borrow or return operation to keep a record of all transactions in the system.
void LoanManager::logEvent(const std::string& message) {
    _activityLog.push_back("[" + timestamp() + "] " + message);
}

// The borrow method implements the logic for borrowing a resource. It performs several checks to enforce the business rules:
// 1. It validates that the user ID and resource ID exist in the system, throwing NotFoundException if either is invalid.
// 2. It checks if the resource can be lent (some resources like Conferences cannot be borrowed at all) and if it is currently available (not already on loan), throwing ResourceUnavailableException if either condition is violated.
// 3. It checks if the user has reached their borrow limit (Students can borrow 1 item, Staff can borrow 2 items, and LibStaff cannot borrow any items), throwing BorrowLimitException if the user cannot borrow more.
// If all checks pass, it marks the resource as borrowed, increments the user's current loan count, adds a new Loan to the list of active loans, and logs the event in the activity log.    

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

    // All checks passed = commit the loan.
    resource->setBorrowed(true);
    user->incrementLoans();
    _activeLoans.emplace_back(user, resource);

    logEvent("BORROW  - " + user->getName() + " borrowed '" +
             resource->getTitle() + "' (" + resource->getID() + ")");
}

// The returnResource method implements the logic for returning a borrowed resource. It performs several checks:
// 1. It validates that the user ID and resource ID exist in the system, throwing NotFoundException if either is invalid.
// 2. It checks if there is an active loan that matches the given user ID and resource ID, throwing NotFoundException if no such loan exists (if the user tries to return a resource they haven't borrowed, or if they try to return a resource that is not currently on loan).
// If the loan is found, it marks the resource as available again, decrements the user's current loan count, removes the loan from the list of active loans, and logs the return event in the activity log. 

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

    // Loan found = commit the return.
    resource->setBorrowed(false);
    user->decrementLoans();
    _activeLoans.erase(it);

    logEvent("RETURN  - " + user->getName() + " returned '" +
             resource->getTitle() + "' (" + resource->getID() + ")");
}