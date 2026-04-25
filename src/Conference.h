// File:       Conference.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

#pragma once
#include "Resource.h"

/**
 * @class Conference
 * @brief A conference proceedings entry. Reference-only —
 *        _canLend is hard-coded to false in the constructor.
 */
class Conference final : public Resource {
private:
    std::string _acronym;   ///< e.g. "OOPSLA", "ICSE"

public:
    Conference(const std::string& id, const std::string& title, const std::string& acronym);
    std::string asString() const override;
    const std::string& getAcronym() const { return _acronym; }
};