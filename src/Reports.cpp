// File:       Reports.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System

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

    sortResources(available, by, order);

    std::cout << "\n--- Available Resources (" << available.size()
              << ", sorted by "
              << (by == SortBy::Author ? "author" : "title") << " "
              << (order == SortOrder::Ascending ? "asc" : "desc") << ") ---\n";
    for (const auto& r : available) {
        std::cout << "  " << *r << '\n';
    }
}

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

    std::sort(sortedLoans.begin(), sortedLoans.end(),
        [by, order](const Loan& a, const Loan& b) {
            const auto ka = sortKey(a.getResource(), by);
            const auto kb = sortKey(b.getResource(), by);
            return order == SortOrder::Ascending ? (ka < kb) : (ka > kb);
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

bool saveBorrowersToFile(const UserList& users, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) return false;

    out << "University Library - Borrowers Report\n";
    out << "=====================================\n\n";

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

void search(const ResourceList& resources, const std::string& keyword) {
    if (keyword.empty()) {
        std::cout << "  (empty keyword - nothing to search)\n";
        return;
    }

    std::vector<std::shared_ptr<Resource>> matches;

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

}  // namespace Reports