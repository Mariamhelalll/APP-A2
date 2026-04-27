// File:       Reports.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:   - Declares the report generation functions for the library management system.
//             -These functions produce various reports based on the current state of resources, users, and loans, such as available resources, loaned resources, current borrowers, and activity logs.
//             - They also include functionality for sorting and filtering the reports based on different criteria, as well as saving certain reports to files.
#pragma once

#include <string>
#include "ResourceList.h"
#include "UserList.h"
#include "LoanManager.h"
// The Reports namespace encapsulates all report generation functions, keeping them organized and separate from other parts of the codebase.
namespace Reports {
    // Enums for sorting options used in the report generation functions. 
    // These allow the user to specify how they want the output to be sorted (by title or author, and in ascending or descending order).

    enum class SortBy    { Title, Author };
    enum class SortOrder { Ascending, Descending };

    // The following functions are declared for generating various reports.
    // Each function takes the necessary data structures as parameters and produces output to the console or a file as appropriate.
    void printAvailable(const ResourceList& resources,
                        SortBy    by    = SortBy::Title,
                        SortOrder order = SortOrder::Ascending);// The printAvailable function generates a report of all resources that are currently available for borrowing.
    // It retrieves the list of resources from the ResourceList, filters them to include only those that can be lent and are not currently borrowed, and then sorts them based on the specified criteria (title or author) and order (ascending or descending).
    // The sorted list is then output to the console. If no resources are available, it informs the user accordingly.


    void printLoaned(const ResourceList& resources,
                     const LoanManager&  manager,
                     SortBy    by    = SortBy::Title,
                     SortOrder order = SortOrder::Ascending); // The printLoaned function generates a report of currently loaned resources, including the borrower and due date information.
    // It retrieves the list of active loans from the LoanManager, filters and sorts them based

    void printBorrowers(const UserList& users); // The printBorrowers function generates a report of all users who currently have outstanding loans.
    // It retrieves the list of users from the UserList, filters them to include only those with current loans, and then outputs their details to the console. If no users have borrowed any resources, it informs the user accordingly.

    bool saveBorrowersToFile(const UserList&    users,
                             const std::string& filename); //   Saves a report of all current borrowers to a specified file. Returns true on success, false on failure.

    void search(const ResourceList& resources,
                const std::string&  keyword); // New function to search for resources based on a keyword that can match the title, author, or acronym.

    void printActivityLog(const LoanManager& manager); // New function to display the activity log of all borrow and return transactions.

    
    void printOverdue(const LoanManager& manager);// New function to generate a report of all currently overdue loans.

}  