// File:       Resource.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 — Library Management System
// Purpose:    - Implements the Resource class, which represents an item in the library that can potentially be borrowed.
//             - It includes properties such as ID, title, borrowability, and loan status, as well as methods for retrieving this information and providing a string representation of the resource for display purposes.

// Resource.cpp
#include "Resource.h"
// The constructor initialises the resource with its ID, title, and whether it can be lent.
Resource::Resource(const std::string& id, const std::string& title, bool canLend)
    : _canLend(canLend), _ID(id), _isBorrowed(false), _title(title) {}