// =============================================================
// File:       main.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Day 5 entry point. Adds every listed-extended
//             feature from the brief:
//               - sort available / loaned reports by title
//                 or author, ascending or descending
//               - save borrowers report to a text file
//               - keyword search across titles / authors
//                 / acronyms (results alphabetical)
//               - display the ordered activity log
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

// ------------------------------------------------------------------
// Display the menu of available actions to the librarian.
// ------------------------------------------------------------------
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
              << "\n  -- Extended --"
              << "\n  10. Search for a keyword"
              << "\n  11. Show activity log"
              << "\n  -------------"
              << "\n   0. Exit"
              << "\n============================================\n";
}

// ------------------------------------------------------------------
// Prompt the user for a sort key (title or author).
// ------------------------------------------------------------------
static Reports::SortBy promptSortBy() {
    std::cout << "  Sort by:\n    1. Title\n    2. Author\n";
    const int choice = readInt("  Choice: ");
    return (choice == 2) ? Reports::SortBy::Author : Reports::SortBy::Title;
}

// ------------------------------------------------------------------
// Prompt the user for a sort direction (asc or desc).
// ------------------------------------------------------------------
static Reports::SortOrder promptSortOrder() {
    std::cout << "  Order:\n    1. Ascending\n    2. Descending\n";
    const int choice = readInt("  Choice: ");
    return (choice == 2) ? Reports::SortOrder::Descending
                         : Reports::SortOrder::Ascending;
}

// ------------------------------------------------------------------
// Handle option 3: borrow a resource.
// ------------------------------------------------------------------
static void handleBorrow(LoanManager& manager) {
    const int user_id         = readInt("User ID:      ");
    const std::string res_id  = readLine("Resource ID:  ");
    try {
        manager.borrow(user_id, res_id);
        std::cout << "  [ok] Loan recorded.\n";
    }
    catch (const LibraryException& e) {
        std::cout << "  [!] " << e.what() << "\n";
    }
}

// ------------------------------------------------------------------
// Handle option 4: return a resource.
// ------------------------------------------------------------------
static void handleReturn(LoanManager& manager) {
    const int user_id         = readInt("User ID:      ");
    const std::string res_id  = readLine("Resource ID:  ");
    try {
        manager.returnResource(user_id, res_id);
        std::cout << "  [ok] Return recorded.\n";
    }
    catch (const LibraryException& e) {
        std::cout << "  [!] " << e.what() << "\n";
    }
}

// ------------------------------------------------------------------
// Handle option 5: show all active loans.
// ------------------------------------------------------------------
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

// ------------------------------------------------------------------
// Handle option 6: sorted available-resources report.
// ------------------------------------------------------------------
static void handleAvailableReport(const ResourceList& resources) {
    const auto by    = promptSortBy();
    const auto order = promptSortOrder();
    Reports::printAvailable(resources, by, order);
}

// ------------------------------------------------------------------
// Handle option 7: sorted loaned-resources report.
// ------------------------------------------------------------------
static void handleLoanedReport(const ResourceList& resources,
                               const LoanManager&  manager)
{
    const auto by    = promptSortBy();
    const auto order = promptSortOrder();
    Reports::printLoaned(resources, manager, by, order);
}

// ------------------------------------------------------------------
// Handle option 9: save borrowers report to a text file.
// ------------------------------------------------------------------
static void handleSaveBorrowers(const UserList& users) {
    const std::string fname = readLine("Output file [borrowers.txt]: ");
    const std::string target = fname.empty() ? "borrowers.txt" : fname;

    if (Reports::saveBorrowersToFile(users, target)) {
        std::cout << "  [ok] Report written to '" << target << "'.\n";
    } else {
        std::cout << "  [!] Could not open '" << target << "' for writing.\n";
    }
}

// ------------------------------------------------------------------
// Handle option 10: keyword search.
// ------------------------------------------------------------------
static void handleSearch(const ResourceList& resources) {
    const std::string keyword = readLine("Keyword: ");
    Reports::search(resources, keyword);
}

// ------------------------------------------------------------------
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

        // Main menu loop.
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
                case 0:  std::cout << "Goodbye.\n"; return 0;
                default: std::cout
                           << "  [!] Unknown option. Please choose 0-11.\n";
            }
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "\nFatal error: " << e.what() << "\n";
        return 1;
    }
}