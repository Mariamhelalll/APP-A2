// File:       Statistics.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Day 7 innovative feature: statistics dashboard.
//             Aggregates data from the LoanManager activity log
//             and active loans to produce summary insights:
//               - total loans ever processed
//               - currently active loans + overdue count
//               - most-borrowed resource
//               - most-active borrower
//             Uses std::map for the aggregations, demonstrating
//             effective use of STL associative containers.

#pragma once

#include "LoanManager.h"

namespace Statistics {

    /// Print a one-screen summary of library activity to std::cout.
    void printDashboard(const LoanManager& manager);

}  // namespace Statistics