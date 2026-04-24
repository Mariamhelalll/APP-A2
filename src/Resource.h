// =============================================================
// File:       Resource.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Abstract base class for every library resource
//             (Book, Journal, Conference). Encodes whether a
//             type is lendable at all (_canLend) and whether
//             a specific item is currently on loan (_isBorrowed).
// =============================================================
#pragma once

#include <string>
#include <iostream>

/**
 * @class Resource
 * @brief Abstract base for all lendable and reference-only items.
 *
 * Cannot be instantiated directly because asString() is pure virtual.
 * Derived classes:
 *   - Book, Journal: lendable (_canLend = true)
 *   - Conference:    reference-only (_canLend = false)
 */
class Resource {
protected:
    bool        _canLend;      ///< false for Conference, true otherwise
    std::string _ID;           ///< unique string ID, e.g. "R001"
    bool        _isBorrowed;   ///< true when currently on loan
    std::string _title;        ///< human-readable title

public:
    Resource(const std::string& id, const std::string& title, bool canLend);

    virtual ~Resource() = default;

    virtual std::string asString() const = 0;

    const std::string& getID()    const { return _ID; }
    const std::string& getTitle() const { return _title; }
    bool canLend()    const { return _canLend; }
    bool isBorrowed() const { return _isBorrowed; }

    void setBorrowed(bool state) { _isBorrowed = state; }

    bool operator<(const Resource& other)  const { return _title < other._title; }
    bool operator==(const Resource& other) const { return _ID == other._ID; }

    friend std::ostream& operator<<(std::ostream& os, const Resource& r) {
        return os << r.asString();
    }
};