// =============================================================
// File:       Reports.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Generates the three core reports required by the
//             brief:
//               - resources currently available for lending
//               - resources currently on loan (with borrower)
//               - users who have borrowed at least one resource
//
//             All report functions print to std::cout via
//             polymorphic operator<< on the underlying objects,
//             keeping a clean separation from business logic.
// =============================================================
#pragma once

#include "ResourceList.h"
#include "UserList.h"
#include "LoanManager.h"

namespace Reports {

    // Prints every resource that is lendable AND not currently borrowed.
    void printAvailable(const ResourceList& resources);

    // Prints every resource currently on loan, along with the borrower.
    // Needs the LoanManager to look up who has each item.
    void printLoaned(const ResourceList& resources,
                     const LoanManager&  manager);

    // Prints every user who currently has at least one outstanding loan.
    void printBorrowers(const UserList& users);

}  // namespace Reports