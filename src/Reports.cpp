// File:       Reports.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Implements the report generation functions declared in Reports.h, including sorting and filtering logic for resources and borrowers, as well as file output for the borrowers report.

#include "Reports.h"
#include "Book.h"
#include "Conference.h"
#include "StringUtils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

namespace Reports {

// The following helper functions are defined in an anonymous namespace to keep them local to this translation unit. 
// They handle sorting of resources based on the specified criteria (title or author) and order (ascending or descending), as well as extracting the appropriate sort key from each resource.
namespace {

    std::string sortKey(const std::shared_ptr<Resource>& r, SortBy by) {
        if (by == SortBy::Author) {
            if (auto book = std::dynamic_pointer_cast<Book>(r)) {
                return book->getAuthor();
            }
            return r->getTitle();
        }
        return r->getTitle();
    }
    // Sorts the given vector of resources in-place based on the specified criteria and order. 
    //This is used by both the printAvailable and printLoaned functions to ensure consistent sorting logic.
    void sortResources(std::vector<std::shared_ptr<Resource>>& items,
                       SortBy by, SortOrder order)
    {
        std::sort(items.begin(), items.end(),
            [by, order](const std::shared_ptr<Resource>& a,
                        const std::shared_ptr<Resource>& b)
            {
                const auto ka = sortKey(a, by);
                const auto kb = sortKey(b, by);
                return order == SortOrder::Ascending ? (ka < kb) : (ka > kb);
            });
    }

}
// The following functions implement the report generation logic for available resources, loaned resources, and current borrowers. 
// They also handle file output for the borrowers report and searching for resources based on a keyword. 
// Each function retrieves the necessary data from the ResourceList, UserList, or LoanManager, applies the appropriate filtering and sorting, and then outputs the results to the console or a file as needed.
void printAvailable(const ResourceList& resources,
                    SortBy by, SortOrder order)
{
    std::vector<std::shared_ptr<Resource>> available;
    const auto& all = resources.getAll();

    std::copy_if(all.begin(), all.end(), std::back_inserter(available),
        [](const std::shared_ptr<Resource>& r) {
            return r->canLend() && !r->isBorrowed();
        });

    if (available.empty()) {
        std::cout << "  (no resources currently available)\n";
        return;
    }

    sortResources(available, by, order); // Sort the available resources based on the specified criteria and order.

    std::cout << "\n--- Available Resources (" << available.size()
              << ", sorted by "
              << (by == SortBy::Author ? "author" : "title") << " "
              << (order == SortOrder::Ascending ? "asc" : "desc") << ") ---\n";
    for (const auto& r : available) {
        std::cout << "  " << *r << '\n';
    }
}
// The printLoaned function generates a report of currently loaned resources, including the borrower and due date information.
// It retrieves the list of active loans from the LoanManager, filters and sorts them based on the specified criteria, and then outputs the details of each loan to the console. 
// If there are no active loans, it informs the user accordingly.
// The report includes indicators for overdue items to highlight them in the output.
void printLoaned(const ResourceList& /*resources*/,
                 const LoanManager&  manager,
                 SortBy by, SortOrder order)
{
    const auto& loans = manager.getActiveLoans();

    if (loans.empty()) {
        std::cout << "  (no resources currently on loan)\n";
        return;
    }

    std::vector<Loan> sortedLoans(loans.begin(), loans.end());
    // Sort the loans based on the specified criteria and order. 
    // The sorting is done by comparing the sort keys of the resources associated with each loan.
    std::sort(sortedLoans.begin(), sortedLoans.end(),
        [by, order](const Loan& a, const Loan& b) {
            const auto ka = sortKey(a.getResource(), by);// Extract the sort key for the first loan's resource based on the specified criteria (title or author).
            const auto kb = sortKey(b.getResource(), by); // Extract the sort key for the second loan's resource based on the specified criteria (title or author).
            return order == SortOrder::Ascending ? (ka < kb) : (ka > kb); // Compare the sort keys and determine the order based on the specified sort order (ascending or descending).
        });
    std::cout << "\n--- Loaned Resources (" << sortedLoans.size()
              << ", sorted by "
              << (by == SortBy::Author ? "author" : "title") << " "
              << (order == SortOrder::Ascending ? "asc" : "desc") << ") ---\n";
    for (const auto& loan : sortedLoans) {
        const auto& res = loan.getResource();
        const auto& per = loan.getPerson();
        std::cout << "  " << *res
                  << "\n      -> borrowed by " << per->getName()
                  << " (ID " << per->getID() << "), due "
                  << loan.dueDateString();
        if (loan.isOverdue()) std::cout << " *** OVERDUE ***";
        std::cout << '\n';
    }
}
// The printBorrowers function generates a report of all users who currently have outstanding loans.
// It retrieves the list of users from the UserList, filters them to include only those with current loans, and then outputs their details to the console. 
// If no users have borrowed any resources, it informs the user accordingly. 
// The report includes the user's name, ID, and the number of items they have currently borrowed, providing a clear overview of active borrowers in the system.
void printBorrowers(const UserList& users) {
    std::vector<std::shared_ptr<Person>> borrowers;
    const auto& all = users.getAll();

    std::copy_if(all.begin(), all.end(), std::back_inserter(borrowers),
        [](const std::shared_ptr<Person>& p) {
            return p->getCurrentLoans() > 0;
        });

    if (borrowers.empty()) {
        std::cout << "  (no users have borrowed any resources)\n";
        return;
    }

    std::cout << "\n--- Current Borrowers (" << borrowers.size() << ") ---\n";
    for (const auto& p : borrowers) {
        std::cout << "  " << *p << '\n';
    }
}
// The saveBorrowersToFile function generates a report of all current borrowers and saves it to a specified file.
// It retrieves the list of users from the UserList, filters them to include only those with current loans, and then writes their details to the file in a human-readable format. 
// If no users have borrowed any resources, it writes a message indicating that as well. The function returns true if the file was successfully opened and written to, or false if there was an error opening the file for writing.
bool saveBorrowersToFile(const UserList& users, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) return false;

    out << "University Library : Borrowers Report\n";
    out << "\n";

    std::size_t count = 0;
    for (const auto& p : users.getAll()) {
        if (p->getCurrentLoans() > 0) {
            out << p->asString() << '\n';
            ++count;
        }
    }

    if (count == 0) {
        out << "(No users have borrowed any resources.)\n";
    } else {
        out << "\nTotal borrowers: " << count << '\n';
    }

    return true;
}
// The search function allows users to search for resources based on a keyword that can match either the title, author (for books), or acronym (for conferences).
// It performs a case-insensitive search through the ResourceList, collects matching resources, and then outputs the results to the console. If no matches are found, it informs the user accordingly.
void search(const ResourceList& resources, const std::string& keyword) {
    if (keyword.empty()) {
        std::cout << "  (empty keyword - nothing to search)\n";
        return;
    }

    std::vector<std::shared_ptr<Resource>> matches; // This vector will hold all resources that match the search keyword.
    // We iterate through all resources in the ResourceList and check if the keyword matches either the title, author (for books), or acronym (for conferences).
    for (const auto& r : resources.getAll()) {
        bool match = StringUtils::containsIgnoreCase(r->getTitle(), keyword);

        if (!match) {
            if (auto book = std::dynamic_pointer_cast<Book>(r)) {
                match = StringUtils::containsIgnoreCase(book->getAuthor(), keyword);
            }
            else if (auto conf = std::dynamic_pointer_cast<Conference>(r)) {
                match = StringUtils::containsIgnoreCase(conf->getAcronym(), keyword);
            }
        }

        if (match) matches.push_back(r);
    }

    if (matches.empty()) {
        std::cout << "  (no resources match '" << keyword << "')\n";
        return;
    }

    std::sort(matches.begin(), matches.end(),
        [](const std::shared_ptr<Resource>& a,
           const std::shared_ptr<Resource>& b) {
            return a->getTitle() < b->getTitle();
        });

    std::cout << "\n--- Search Results for '" << keyword << "' ("
              << matches.size() << ") ---\n";
    for (const auto& r : matches) {
        std::cout << "  " << *r << '\n';
    }
}
// The printActivityLog function retrieves the activity log from the LoanManager and displays it in a human-readable format.
// If the log is empty, it informs the user accordingly.
void printActivityLog(const LoanManager& manager) {
    const auto& log = manager.getActivityLog();

    if (log.empty()) {
        std::cout << "  (activity log is empty)\n";
        return;
    }

    std::cout << "\n--- Activity Log (" << log.size() << " events) ---\n";
    for (const auto& entry : log) {
        std::cout << "  " << entry << '\n';
    }
}
// The printOverdue function generates a report of all currently overdue loans.
// It retrieves the list of active loans from the LoanManager, filters them to include only those that are overdue, and then outputs their details to the console. If there are no overdue loans, it informs the user accordingly. 
// The report includes the resource title, borrower name, and due date, with an indicator for overdue items to highlight them in the output.
void printOverdue(const LoanManager& manager) {
    const auto& loans = manager.getActiveLoans();

    std::vector<Loan> overdue;
    std::copy_if(loans.begin(), loans.end(), std::back_inserter(overdue),
        [](const Loan& l) { return l.isOverdue(); });

    if (overdue.empty()) {
        std::cout << "  (no overdue loans)\n";
        return;
    }

    std::cout << "\n--- Overdue Loans (" << overdue.size() << ") ---\n";
    for (const auto& l : overdue) {
        std::cout << "  " << l.asString() << '\n';
    }
}

}  