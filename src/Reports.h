// =============================================================
// File:       Reports.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Generates the core reports required by the brief
//             plus the Day-5 listed-extended features:
//               - sortable available/loaned reports (title or
//                 author, ascending or descending)
//               - save borrowers report to a text file
//               - keyword search over title/author/acronym
//               - display the ordered activity log
// =============================================================
#pragma once

#include <string>
#include "ResourceList.h"
#include "UserList.h"
#include "LoanManager.h"

namespace Reports {

    // Sort options used by the extended report features.
    // enum class is used (not plain enum) for type safety:
    // values are strongly scoped, preventing accidental comparison
    // with unrelated integers.
    enum class SortBy    { Title, Author };
    enum class SortOrder { Ascending, Descending };

    // ---- Core reports (also sortable via parameters) ------------
    void printAvailable(const ResourceList& resources,
                        SortBy    by    = SortBy::Title,
                        SortOrder order = SortOrder::Ascending);

    void printLoaned(const ResourceList& resources,
                     const LoanManager&  manager,
                     SortBy    by    = SortBy::Title,
                     SortOrder order = SortOrder::Ascending);

    void printBorrowers(const UserList& users);

    // ---- Day-5 extended features --------------------------------

    // Save the "users who have borrowed" report to a text file.
    // Creates or overwrites the file. Returns true on success.
    bool saveBorrowersToFile(const UserList&    users,
                             const std::string& filename);

    // Keyword search over title, author (Book) and acronym
    // (Conference). Results are printed alphabetically by title.
    void search(const ResourceList& resources,
                const std::string&  keyword);

    // Display the ordered activity log of every borrow/return event.
    void printActivityLog(const LoanManager& manager);

}  // namespace Reports