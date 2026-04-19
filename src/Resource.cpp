// =============================================================
// File:       <Resource.cpp>
// Author:     <Maryam Mohamed>
// Student ID: <29073094>
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 — Library Management System
// Purpose:    <one-line description>
// =============================================================

// Resource.cpp
#include "Resource.h"

Resource::Resource(const std::string& id, const std::string& title, bool canLend)
    : _canLend(canLend), _ID(id), _isBorrowed(false), _title(title) {}