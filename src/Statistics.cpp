// =============================================================
// File:       Statistics.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// =============================================================
#include "Statistics.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

namespace Statistics {

namespace {
    std::size_t countBorrowEvents(const std::vector<std::string>& log) {
        return std::count_if(log.begin(), log.end(),
            [](const std::string& entry) {
                return entry.find("BORROW") != std::string::npos;
            });
    }
}

void printDashboard(const LoanManager& manager) {
    const auto& active = manager.getActiveLoans();
    const auto& log    = manager.getActivityLog();

    const std::size_t totalLoans = countBorrowEvents(log);
    const auto overdueCount = std::count_if(active.begin(), active.end(),
        [](const Loan& l) { return l.isOverdue(); });

    std::map<std::string, int> resourceCounts;
    std::map<std::string, int> borrowerCounts;

    for (const auto& loan : active) {
        ++resourceCounts[loan.getResource()->getTitle()];
        ++borrowerCounts[loan.getPerson()->getName()];
    }

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

    const auto topResource = findTopOf(resourceCounts);
    const auto topBorrower = findTopOf(borrowerCounts);

    std::cout << "\n========== Library Statistics ==========\n";
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
    std::cout << "========================================\n";
}

}  // namespace Statistics