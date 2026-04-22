// =============================================================
// File:       Reports.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// =============================================================
#include "Reports.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <vector>

namespace Reports {

// ------------------------------------------------------------------
// Core report 1: available resources.
// Uses std::copy_if to filter resources in a single pass.
// ------------------------------------------------------------------
void printAvailable(const ResourceList& resources) {
    std::vector<std::shared_ptr<Resource>> available;
    const auto& all = resources.getAll();

    std::copy_if(all.begin(), all.end(), std::back_inserter(available),
        [](const std::shared_ptr<Resource>& r) {
            // Lendable (not a Conference) AND not currently borrowed.
            return r->canLend() && !r->isBorrowed();
        });

    if (available.empty()) {
        std::cout << "  (no resources currently available)\n";
        return;
    }

    std::cout << "\n--- Available Resources (" << available.size() << ") ---\n";
    for (const auto& r : available) {
        std::cout << "  " << *r << '\n';
    }
}

// ------------------------------------------------------------------
// Core report 2: currently loaned-out resources, with borrower.
// Walks the active-loans list rather than re-scanning everything,
// since the manager already has this information indexed.
// ------------------------------------------------------------------
void printLoaned(const ResourceList& /*resources*/,
                 const LoanManager&  manager)
{
    const auto& loans = manager.getActiveLoans();

    if (loans.empty()) {
        std::cout << "  (no resources currently on loan)\n";
        return;
    }

    std::cout << "\n--- Loaned Resources (" << loans.size() << ") ---\n";
    for (const auto& loan : loans) {
        const auto& res = loan.getResource();
        const auto& per = loan.getPerson();
        std::cout << "  " << *res
                  << "\n      -> borrowed by " << per->getName()
                  << " (ID " << per->getID() << ")\n";
    }
}

// ------------------------------------------------------------------
// Core report 3: users who have borrowed at least one resource.
// ------------------------------------------------------------------
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

}  // namespace Reports