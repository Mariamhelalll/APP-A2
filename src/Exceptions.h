// =============================================================
// File:       Exceptions.h
// Author:     Maryam Mohamed 
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Custom exception hierarchy for business-rule errors.
//             All inherit from std::runtime_error so a single
//             catch can handle any library-level failure.
// =============================================================
#pragma once

#include <stdexcept>
#include <string>

// Root of our exception hierarchy. Catching this catches every
// library-level business error.
class LibraryException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

// Thrown when a user tries to borrow beyond their allowed limit.
class BorrowLimitException : public LibraryException {
public:
    explicit BorrowLimitException(const std::string& msg)
        : LibraryException(msg) {}
};

// Thrown when a resource cannot be borrowed (already on loan,
// or not lendable in the first place, e.g. Conference).
class ResourceUnavailableException : public LibraryException {
public:
    explicit ResourceUnavailableException(const std::string& msg)
        : LibraryException(msg) {}
};

// Thrown when a user ID or resource ID is not found in the system.
class NotFoundException : public LibraryException {
public:
    explicit NotFoundException(const std::string& msg)
        : LibraryException(msg) {}
};