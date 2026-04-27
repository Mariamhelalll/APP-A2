
// File:       main.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    Day 7 entry point. Adds the two innovative
//             extended features:
//               12. Overdue loans report (uses <chrono>)
//               13. Statistics dashboard (uses std::map)
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
    std::cout << "\n MAIN MENU :"
              << "\n  Catalogue :"
              << "\n   1 ) List all resources"
              << "\n   2 ) List all users"
              << "\n  Loans :"
              << "\n   3 ) Borrow a resource"
              << "\n   4 ) Return a resource"
              << "\n   5 ) Show active loans"
              << "\n  Reports :"
              << "\n   6 ) Report: resources available (sorted)"
              << "\n   7 ) Report: resources on loan (sorted)"
              << "\n   8 ) Report: users who have borrowed"
              << "\n   9 ) Save borrowers report to file"
              << "\n  Search & Logs :"
              << "\n  10 ) Search for a keyword"
              << "\n  11 ) Show activity log"
              << "\n  Innovative :"
              << "\n  12 ) Overdue loans report"
              << "\n  13 ) Statistics dashboard"
              << "\n "
              << "\n   0 ) Exit"
              << "\n";
}
// Prompts for sorting options and returns the corresponding enum values. These are used in the report generation functions to determine how to sort the output.
static Reports::SortBy promptSortBy() {
    std::cout << "  Sort by:\n    1) Title\n    2) Author\n";
    const int choice = readInt("  Choice: ");
    return (choice == 2) ? Reports::SortBy::Author : Reports::SortBy::Title; // Default to Title if the input is invalid.
}

static Reports::SortOrder promptSortOrder() {
    std::cout << "  Order:\n    1) Ascending\n    2) Descending\n";
    const int choice = readInt("  Choice: ");
    return (choice == 2) ? Reports::SortOrder::Descending // Default to Ascending if the input is invalid.
                         : Reports::SortOrder::Ascending; // Default to Ascending if the input is invalid.
}
// The following handler functions encapsulate the logic for each menu action, keeping the main loop clean and focused on user interaction. They also handle exceptions thrown by the LoanManager and report generation functions, allowing for graceful error handling without crashing the program.
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
// The handleReturn function prompts the user for a user ID and resource ID, then attempts to process the return through the LoanManager. 
// If the return is successful, it confirms with a message. 
// If any exceptions are thrown (such as NotFoundException if the user or resource doesn't exist, or if the loan doesn't exist), it catches them and displays the error message without crashing the program.
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
// The showActiveLoans function retrieves the list of active loans from the LoanManager and displays them in a human-readable format.
// If there are no active loans, it informs the user accordingly.
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
// The handleAvailableReport and handleLoanedReport functions prompt the user for sorting options and then call the corresponding report generation functions in the Reports namespace.
// They pass the ResourceList and LoanManager as needed to generate the reports based on the current state of the system.
static void handleAvailableReport(const ResourceList& resources) {
    const auto by    = promptSortBy();
    const auto order = promptSortOrder();
    Reports::printAvailable(resources, by, order);
}
// The handleLoanedReport function prompts the user for sorting options and then calls the Reports::printLoaned function to generate a report of currently loaned resources, sorted according to the user's preferences.
static void handleLoanedReport(const ResourceList& resources,
                               const LoanManager&  manager)
{
    const auto by    = promptSortBy();
    const auto order = promptSortOrder();
    Reports::printLoaned(resources, manager, by, order);
}
// The handleSaveBorrowers function prompts the user for an output filename (defaulting to "borrowers.txt" if left blank) and then calls the Reports::saveBorrowersToFile function to save a report of all borrowers to the specified file.
// It confirms success or reports an error if the file cannot be opened for writing.
static void handleSaveBorrowers(const UserList& users) {
    const std::string fname = readLine("Output file [borrowers.txt]: ");
    const std::string target = fname.empty() ? "borrowers.txt" : fname;

    if (Reports::saveBorrowersToFile(users, target)) {
        std::cout << "  [ok] Report written to '" << target << "'.\n";
    } else {
        std::cout << "  [!] Could not open '" << target << "' for writing.\n";
    }
}
// The handleSearch function prompts the user for a keyword and then calls the Reports::search function to search for that keyword in the resource catalogue.
// The search results are displayed to the user.
static void handleSearch(const ResourceList& resources) {
    const std::string keyword = readLine("Keyword: ");
    Reports::search(resources, keyword);
}
// The main function initializes the ResourceList and UserList from their respective data files, creates a LoanManager to handle borrowing and returning, and then enters a loop to display the menu and process user input.
// It uses a try-catch block to handle any fatal errors that occur during initialization (such as file loading errors) and reports them to the user before exiting. 
// Within the loop, it calls the appropriate handler functions based on the user's menu choice, allowing for a clean separation of concerns and modular code organisation.

int main() {
    std::cout << "\n"
              << "  University Library Management System\n"
              << "  Staff: Librarian: Maryam Mohamed\n"
              << "\n";
    
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