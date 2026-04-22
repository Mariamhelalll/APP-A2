// =============================================================
// File:       main.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Day 4 entry point. Extends Day 3's menu with the
//             three core reports required by the brief:
//               - resources currently available
//               - resources currently on loan
//               - users who have borrowed
//             Every other behaviour remains as Day 3.
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
    std::cout << "\n================ MAIN MENU ================"
              << "\n  -- Catalogue --"
              << "\n   1. List all resources"
              << "\n   2. List all users"
              << "\n  -- Loans --"
              << "\n   3. Borrow a resource"
              << "\n   4. Return a resource"
              << "\n   5. Show active loans"
              << "\n  -- Reports --"
              << "\n   6. Report: resources available"
              << "\n   7. Report: resources on loan"
              << "\n   8. Report: users who have borrowed"
              << "\n  -------------"
              << "\n   0. Exit"
              << "\n===========================================\n";
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
                  << users.getAll().size()     << " users.\n";

        // Main menu loop.
        while (true) {
            showMenu();
            const int choice = readInt("Choice: ");

            switch (choice) {
                case 1:
                    std::cout << "\n--- Resources ---\n";
                    resources.printResourceList();
                    break;
                case 2:
                    std::cout << "\n--- Users ---\n";
                    users.printUserList();
                    break;
                case 3:
                    handleBorrow(manager);
                    break;
                case 4:
                    handleReturn(manager);
                    break;
                case 5:
                    showActiveLoans(manager);
                    break;
                case 6:
                    Reports::printAvailable(resources);
                    break;
                case 7:
                    Reports::printLoaned(resources, manager);
                    break;
                case 8:
                    Reports::printBorrowers(users);
                    break;
                case 0:
                    std::cout << "Goodbye.\n";
                    return 0;
                default:
                    std::cout << "  [!] Unknown option. Please choose 0-8.\n";
            }
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "\nFatal error: " << e.what() << "\n";
        return 1;
    }
}