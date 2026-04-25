#**APP-A2**

1) To run the code: 
./build.sh
./library

2) To push the code to github:
git add .
git commit -m "Day 7: final"
git push

==============================================================
  University Library Management System
  CMP2811 Applied Programming Paradigms - Assessment Item 2
==============================================================

Author:     Maryam Mohamed
Student ID: 29073094
Module:     CMP2811 Applied Programming Paradigms
Submission: Assessment Item 2

--------------------------------------------------------------
PROJECT OVERVIEW
--------------------------------------------------------------
A command-line library management system written in C++17.
The program is operated by a librarian who can manage a
catalogue of resources (books, journals, conference proceedings)
and a list of system users (students, staff, library staff).
It enforces every borrowing rule from the assignment brief and
provides reports, search, statistics, and a persistent activity
log throughout the session.

--------------------------------------------------------------
HOW TO BUILD:
--------------------------------------------------------------
1. Open APP-A2.sln in Visual Studio 2022.
2. Confirm the build target at the top of the window:
       Configuration: Debug
       Platform:      x64
3. Build the solution:  Build > Build Solution  (Ctrl+Shift+B).
   Expected: "Build: 1 succeeded, 0 failed".

--------------------------------------------------------------
HOW TO RUN
--------------------------------------------------------------
Press Ctrl+F5 (Debug > Start Without Debugging).

The program reads two text files at startup:
   data/resources.txt   - 10 sample resources
   data/users.txt       - 8 sample users

Both files are loaded automatically because the project's
Working Directory is set to $(ProjectDir) under
Properties > Debugging.

--------------------------------------------------------------
PROJECT STRUCTURE
--------------------------------------------------------------
APP-A2/
  APP-A2.sln                   Solution file
  APP-A2.vcxproj               Project file
  APP-A2.vcxproj.filters       Solution Explorer folder layout
  README.txt                   This file
  data/
    resources.txt              Resource catalogue (pipe-delimited)
    users.txt                  System users (pipe-delimited)
  src/
    Resource.h / .cpp          Abstract base for all resources
    Book.h / .cpp              Lendable book (author field)
    Journal.h / .cpp           Lendable journal (ISSN field)
    Conference.h / .cpp        Reference-only conference (acronym)
    Person.h / .cpp            Abstract base for all users
    Student.h / .cpp           Borrow limit = 1
    Staff.h / .cpp             Borrow limit = 2
    LibStaff.h / .cpp          Borrow limit = 0 (cannot borrow)
    Loan.h / .cpp              Single borrow transaction with due date
    LoanManager.h / .cpp       Borrow / return business-logic engine
    ResourceList.h / .cpp      Loads + owns resources via factory
    UserList.h / .cpp          Loads + owns users via factory
    Reports.h / .cpp           All reports (core + extended)
    Statistics.h / .cpp        Innovative statistics dashboard
    StringUtils.h              split() + case-insensitive search
    Exceptions.h               Custom business-rule exceptions
    InputHelpers.h             Robust input reading helpers
    main.cpp                   Menu loop entry point

--------------------------------------------------------------
MENU OVERVIEW
--------------------------------------------------------------
After loading the catalogue, the program displays a 14-option
menu grouped into six sections:

  Catalogue
    1. List all resources
    2. List all users
  Loans
    3. Borrow a resource
    4. Return a resource
    5. Show active loans
  Reports
    6. Report: resources available (sortable)
    7. Report: resources on loan (sortable)
    8. Report: users who have borrowed
    9. Save borrowers report to file
  Search & Logs
   10. Search for a keyword
   11. Show activity log
  Innovative
   12. Overdue loans report
   13. Statistics dashboard
   0. Exit

--------------------------------------------------------------
FEATURES IMPLEMENTED
--------------------------------------------------------------
Core (all from brief):
  - Resources loaded from text file with unique string IDs
    (R001, R002, ...)
  - Users loaded from text file with unique integer IDs
    (1001, 1002, ...)
  - Borrowing with all five business rules enforced:
      * Students may borrow max 1 resource
      * Staff may borrow max 2 resources
      * Library staff may borrow none
      * Each Book/Journal can be borrowed only once at a time
      * Conferences cannot be borrowed at all
  - Returning resources, with records updated correctly
  - List of resources currently available for lending
  - Report of resources currently loaned out
  - Report of users who have borrowed a resource

Listed extended (all from brief):
  - Sort available list by title or author, asc or desc
  - Sort loaned list by title or author, asc or desc
  - Save borrowers report to a user-specified text file
  - Keyword search across title, author (Book) and acronym
    (Conference); case-insensitive; results alphabetical
  - Ordered activity log of every borrow / return event,
    each entry timestamped, displayable on console

Innovative extended (Day 7 additions):
  - Due dates: every loan has a 14-day default loan period,
    computed at borrow time using std::chrono::system_clock.
  - Overdue detection: option 12 lists only overdue loans;
    overdue items are also flagged "*** OVERDUE ***" wherever
    a loan is displayed.
  - Statistics dashboard: option 13 shows total loans ever
    processed, currently active, currently overdue,
    most-borrowed resource, and most-active borrower. Uses
    std::map for the per-resource and per-borrower counts.

--------------------------------------------------------------
SAMPLE TEST WALK-THROUGH
--------------------------------------------------------------
After the program has loaded:

   3 -> 1001 -> R001        (Alice borrows a book; success)
   3 -> 1001 -> R002        (Alice over-limit; rejected)
   3 -> 1002 -> R001        (R001 already loaned; rejected)
   3 -> 1001 -> R008        (Conference; rejected)
   3 -> 1008 -> R002        (LibStaff; rejected)
   6 -> 1   -> 2            (sort available, title desc)
  10 -> C++                 (case-insensitive search)
  13                        (statistics dashboard)
   4 -> 1001 -> R001        (Alice returns the book)
   0                        (exit)

--------------------------------------------------------------
OBJECT-ORIENTED DESIGN
--------------------------------------------------------------
The system uses two parallel inheritance hierarchies:

  Resource (abstract)
    +-- Book        (lendable, has author)
    +-- Journal     (lendable, has ISSN)
    +-- Conference  (reference only, has acronym)

  Person (abstract)
    +-- Student     (borrow limit = 1)
    +-- Staff       (borrow limit = 2)
    +-- LibStaff    (borrow limit = 0)

The two abstract base classes are non-instantiable (pure virtual
asString()) and have virtual destructors. Each concrete leaf is
marked `final`. Operator overloads (<, ==, <<) are provided
symmetrically across Resource, Person and Loan.

A Loan binds one Person to one Resource via std::shared_ptr,
participating in shared ownership with the two collection
classes. The LoanManager class orchestrates borrow/return
operations against the two catalogues, throwing typed
exceptions (BorrowLimitException, ResourceUnavailableException,
NotFoundException) on rule violations.

--------------------------------------------------------------
CONTEMPORARY C++ FEATURES USED
--------------------------------------------------------------
  - std::shared_ptr / std::make_shared (smart-pointer ownership)
  - std::vector (every collection)
  - std::find_if, std::copy_if, std::count_if, std::sort,
    std::search, std::max_element (STL algorithms)
  - Lambda expressions (predicates and comparators)
  - enum class (type-safe sort options)
  - std::chrono (loan dates, due dates, overdue detection)
  - std::map (statistics aggregations)
  - RAII (file streams, smart pointers)
  - dynamic_pointer_cast (type-safe downcasts in search and sort)
  - constexpr, override, final (compile-time correctness)
  - Custom exception hierarchy inheriting std::runtime_error

--------------------------------------------------------------
NOTES FOR THE MARKER
--------------------------------------------------------------
* The program assumes data/resources.txt and data/users.txt
  exist relative to the project directory. The Visual Studio
  Working Directory is set to $(ProjectDir) for this purpose.
* Build target tested: x64 / Debug under MSVC, also g++ 13.3
  with -Wall -Wextra -Wpedantic (zero warnings).
* The activity log timestamps use localtime_s on Windows and
  localtime_r on POSIX, selected via #ifdef _WIN32. This avoids
  the deprecated-localtime warning under MSVC.

==============================================================