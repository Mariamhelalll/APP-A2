// File:       Statistics.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Implements the Statistics dashboard feature, which provides insights into borrowing trends and patterns in the library.
// -     The dashboard includes metrics such as total loans processed, currently active loans, overdue loans, most borrowed resource, and most active borrower. 
// -     The implementation uses standard library algorithms and data structures to compute these

#include "Statistics.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
// The Statistics namespace contains functions related to generating a statistics dashboard for the library management system.
// The printDashboard function computes and displays various statistics about the library's borrowing activity, such as total loans processed, currently active loans, overdue loans, most borrowed resource, and most active borrower.
namespace Statistics {

namespace {
    std::size_t countBorrowEvents(const std::vector<std::string>& log) {
        return std::count_if(log.begin(), log.end(),
            [](const std::string& entry) {
                return entry.find("BORROW") != std::string::npos;
            });
    }
}
// The printDashboard function computes and displays various statistics about the library's borrowing activity, such as total loans processed, currently active loans, overdue loans, most borrowed resource, and most active borrower.
// It uses standard library algorithms and data structures to compute these metrics based on the active loans and activity log provided by the LoanManager.
void printDashboard(const LoanManager& manager) {
    const auto& active = manager.getActiveLoans();
    const auto& log    = manager.getActivityLog();

    // Compute total loans processed by counting "BORROW" entries in the activity log, and count currently active and overdue loans from the list of active loans.
    const std::size_t totalLoans = countBorrowEvents(log);
    const auto overdueCount = std::count_if(active.begin(), active.end(),
        [](const Loan& l) { return l.isOverdue(); });

    std::map<std::string, int> resourceCounts;
    std::map<std::string, int> borrowerCounts;

    // Count the number of active loans for each resource and borrower to determine the most borrowed resource and most active borrower.
    for (const auto& loan : active) {
        ++resourceCounts[loan.getResource()->getTitle()];
        ++borrowerCounts[loan.getPerson()->getName()];
    }

    // Helper lambda to find the key with the maximum value in a map, used to identify the most borrowed resource and most active borrower.
    // If the map is empty, it returns a default pair indicating no data.
    auto findTopOf = [](const std::map<std::string, int>& m)
        -> std::pair<std::string, int>
    {
        if (m.empty()) return { "(none)", 0 };
        auto it = std::max_element(m.begin(), m.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });
        return { it->first, it->second };
    };

    // Find the most borrowed resource and most active borrower using the helper lambda function.
    const auto topResource = findTopOf(resourceCounts);
    const auto topBorrower = findTopOf(borrowerCounts);

    std::cout << "\nLibrary Statistics :\n";
    std::cout << "  Total loans ever processed:  " << totalLoans << "\n";
    std::cout << "  Currently active loans:      " << active.size() << "\n";
    std::cout << "  Currently overdue:           " << overdueCount << "\n";

    if (active.empty()) {
        std::cout << "  Most-borrowed resource:      (no active loans)\n";
        std::cout << "  Most-active borrower:        (no active loans)\n";
    } else {
        std::cout << "  Most-borrowed resource:      " << topResource.first
                  << " (" << topResource.second << ")\n";
        std::cout << "  Most-active borrower:        " << topBorrower.first
                  << " (" << topBorrower.second << ")\n";
    }
    std::cout << "\n";
}

}  