// =============================================================
// File:       main.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Day 7 entry point. Adds the two innovative
//             extended features:
//               12. Overdue loans report (uses <chrono>)
//               13. Statistics dashboard (uses std::map)
// =============================================================
#include <iostream>
#include <stdexcept>
#include <string>

#include "ResourceList.h"
#include "UserList.h"
#include "LoanManager.h"
#include "Exceptions.h"
#include "InputHelpers.h"
#include "Reports.h"
#include "Statistics.h"

static void showMenu() {
    std::cout << "\n================= MAIN MENU ================="
              << "\n  -- Catalogue --"
              << "\n   1. List all resources"
              << "\n   2. List all users"
              << "\n  -- Loans --"
              << "\n   3. Borrow a resource"
              << "\n   4. Return a resource"
              << "\n   5. Show active loans"
              << "\n  -- Reports --"
              << "\n   6. Report: resources available (sorted)"
              << "\n   7. Report: resources on loan (sorted)"
              << "\n   8. Report: users who have borrowed"
              << "\n   9. Save borrowers report to file"
              << "\n  -- Search & Logs --"
              << "\n  10. Search for a keyword"
              << "\n  11. Show activity log"
              << "\n  -- Innovative --"
              << "\n  12. Overdue loans report"
              << "\n  13. Statistics dashboard"
              << "\n  -------------"
              << "\n   0. Exit"
              << "\n============================================\n";
}

static Reports::SortBy promptSortBy() {
    std::cout << "  Sort by:\n    1. Title\n    2. Author\n";
    const int choice = readInt("  Choice: ");
    return (choice == 2) ? Reports::SortBy::Author : Reports::SortBy::Title;
}

static Reports::SortOrder promptSortOrder() {
    std::cout << "  Order:\n    1. Ascending\n    2. Descending\n";
    const int choice = readInt("  Choice: ");
    return (choice == 2) ? Reports::SortOrder::Descending
                         : Reports::SortOrder::Ascending;
}

static void handleBorrow(LoanManager& manager) {
    const int user_id        = readInt("User ID:      ");
    const std::string res_id = readLine("Resource ID:  ");
    try {
        manager.borrow(user_id, res_id);
        std::cout << "  [ok] Loan recorded.\n";
    }
    catch (const LibraryException& e) {
        std::cout << "  [!] " << e.what() << "\n";
    }
}

static void handleReturn(LoanManager& manager) {
    const int user_id        = readInt("User ID:      ");
    const std::string res_id = readLine("Resource ID:  ");
    try {
        manager.returnResource(user_id, res_id);
        std::cout << "  [ok] Return recorded.\n";
    }
    catch (const LibraryException& e) {
        std::cout << "  [!] " << e.what() << "\n";
    }
}

static void showActiveLoans(const LoanManager& manager) {
    const auto& loans = manager.getActiveLoans();
    if (loans.empty()) {
        std::cout << "  (no active loans)\n";
        return;
    }
    std::cout << "\n--- Active Loans (" << loans.size() << ") ---\n";
    for (const auto& loan : loans) {
        std::cout << "  " << loan.asString() << "\n";
    }
}

static void handleAvailableReport(const ResourceList& resources) {
    const auto by    = promptSortBy();
    const auto order = promptSortOrder();
    Reports::printAvailable(resources, by, order);
}

static void handleLoanedReport(const ResourceList& resources,
                               const LoanManager&  manager)
{
    const auto by    = promptSortBy();
    const auto order = promptSortOrder();
    Reports::printLoaned(resources, manager, by, order);
}

static void handleSaveBorrowers(const UserList& users) {
    const std::string fname = readLine("Output file [borrowers.txt]: ");
    const std::string target = fname.empty() ? "borrowers.txt" : fname;

    if (Reports::saveBorrowersToFile(users, target)) {
        std::cout << "  [ok] Report written to '" << target << "'.\n";
    } else {
        std::cout << "  [!] Could not open '" << target << "' for writing.\n";
    }
}

static void handleSearch(const ResourceList& resources) {
    const std::string keyword = readLine("Keyword: ");
    Reports::search(resources, keyword);
}

int main() {
    std::cout << "===============================================\n"
              << "  University Library Management System\n"
              << "  Staff: Librarian [Your Name]\n"
              << "===============================================\n\n";

    try {
        ResourceList resources("data/resources.txt");
        UserList     users("data/users.txt");
        LoanManager  manager(resources, users);

        std::cout << "Loaded " << resources.getAll().size() << " resources and "
                  << users.getAll().size() << " users.\n";

        while (true) {
            showMenu();
            const int choice = readInt("Choice: ");

            switch (choice) {
                case 1:  std::cout << "\n--- Resources ---\n";
                         resources.printResourceList();           break;
                case 2:  std::cout << "\n--- Users ---\n";
                         users.printUserList();                   break;
                case 3:  handleBorrow(manager);                   break;
                case 4:  handleReturn(manager);                   break;
                case 5:  showActiveLoans(manager);                break;
                case 6:  handleAvailableReport(resources);        break;
                case 7:  handleLoanedReport(resources, manager);  break;
                case 8:  Reports::printBorrowers(users);          break;
                case 9:  handleSaveBorrowers(users);              break;
                case 10: handleSearch(resources);                 break;
                case 11: Reports::printActivityLog(manager);      break;
                case 12: Reports::printOverdue(manager);          break;
                case 13: Statistics::printDashboard(manager);     break;
                case 0:  std::cout << "Goodbye.\n"; return 0;
                default: std::cout
                           << "  [!] Unknown option. Please choose 0-13.\n";
            }
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "\nFatal error: " << e.what() << "\n";
        return 1;
    }
}