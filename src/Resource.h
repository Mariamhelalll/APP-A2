// File:       Resource.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    - Abstract base class for every library resource (Book, Journal, Conference). 
//             - Encodes whether atype is lendable at all (_canLend) and whether a specific item is currently on loan (_isBorrowed).

#pragma once

#include <string>
#include <iostream>

/**
 * @class Resource
 * @brief Abstract base for all lendable and reference-only items.
 */
// The Resource class represents an item in the library that can potentially be borrowed.
// It has an ID, a title, a flag indicating whether it can be lent, and a flag indicating whether it is currently on loan.
// The constructor initialises these values, and the asString method provides a string representation of the resource for display purposes.
// The class also includes methods for retrieving the ID, title, borrowability, and loan status of the resource, as well as a method for setting the loan status.
// The comparison operators allow resources to be compared based on their title for sorting purposes, and based on their ID for
class Resource {
protected:
    bool        _canLend;      ///< false for Conference, true otherwise
    std::string _ID;           ///< unique string ID, eg: "R001"
    bool        _isBorrowed;   ///< true when currently on loan
    std::string _title;        ///< human-readable title
// The constructor initialises the resource with its ID, title, and whether it can be lent.
// The asString method provides a human-readable description of the resource, including its ID, title, and loan status.
public:
    Resource(const std::string& id, const std::string& title, bool canLend);// The constructor initialises the resource with its ID, title, and whether it can be lent.

    virtual ~Resource() = default;  // The asString method provides a human-readable description of the resource, including its ID, title, and loan status.

    virtual std::string asString() const = 0; // The getID method returns the unique string ID of the resource, which is used for identification and lookup purposes in the system.

    const std::string& getID()    const { return _ID; } // The getTitle method returns the human-readable title of the resource, which is used for display purposes in reports and listings.
    const std::string& getTitle() const { return _title; } // The canLend method returns true if the resource can be lent (is borrowable), which is determined by its type (eg: Conference cannot be lent).
    bool canLend()    const { return _canLend; } // The isBorrowed method returns true if the resource is currently on loan, which is tracked by the LoanManager when resources are borrowed or returned.
    bool isBorrowed() const { return _isBorrowed; } // The setBorrowed method allows the loan status of the resource to be updated when it is borrowed or returned. This is used by the LoanManager to track which resources are currently on loan.

    void setBorrowed(bool state) { _isBorrowed = state; } // The comparison operators allow resources to be compared based on their title for sorting purposes, and based on their ID for equality checks.

    bool operator<(const Resource& other)  const { return _title < other._title; } // The operator< allows resources to be compared based on their title, which enables sorting of resources in reports and listings.
    bool operator==(const Resource& other) const { return _ID == other._ID; } //    The operator== allows resources to be compared based on their ID, which is used for identification and lookup purposes in the system.
    // Enables "std::cout << resource" to print the resource's string representation.
 
    // The friend declaration allows the operator<< function to access the private and protected members of the Resource class in order to output its string representation when using std::cout.
    friend std::ostream& operator<<(std::ostream& os, const Resource& r) {
        return os << r.asString();
    }
};