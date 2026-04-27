// File:       Statistics.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:   - Declares the Statistics namespace and the printDashboard function, which generates a summary of library activity based on data from the LoanManager.

#pragma once

#include "LoanManager.h"

namespace Statistics {

    /// Print a one-screen summary of library activity to std::cout.
    void printDashboard(const LoanManager& manager);

}  