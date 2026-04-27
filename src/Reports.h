// File:       Reports.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Generates the core, listed-extended, and Day-7
//             innovative reports.
#pragma once

#include <string>
#include "ResourceList.h"
#include "UserList.h"
#include "LoanManager.h"

namespace Reports {

    enum class SortBy    { Title, Author };
    enum class SortOrder { Ascending, Descending };

    void printAvailable(const ResourceList& resources,
                        SortBy    by    = SortBy::Title,
                        SortOrder order = SortOrder::Ascending);

    void printLoaned(const ResourceList& resources,
                     const LoanManager&  manager,
                     SortBy    by    = SortBy::Title,
                     SortOrder order = SortOrder::Ascending);

    void printBorrowers(const UserList& users);

    bool saveBorrowersToFile(const UserList&    users,
                             const std::string& filename);

    void search(const ResourceList& resources,
                const std::string&  keyword);

    void printActivityLog(const LoanManager& manager);

    /// Day 7 innovative: print only loans whose due date has passed.
    void printOverdue(const LoanManager& manager);

}  // namespace Reports