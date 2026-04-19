// main.cpp
#include <iostream>
#include <memory>

#include "Book.h"
#include "Journal.h"
#include "Conference.h"
#include "Student.h"
#include "Staff.h"
#include "LibStaff.h"
#include "ResourceList.h"
#include "UserList.h"

int main() {
    std::cout << "===============================================\n";
    std::cout << "  University Library Management System\n";
    std::cout << "  Staff: Librarian [Your Name]\n";
    std::cout << "===============================================\n\n";

    // Day 1 smoke test — polymorphism works through base pointers.
    std::shared_ptr<Resource> r1 = std::make_shared<Book>("R001", "The C++ Programming Language", "Bjarne Stroustrup");
    std::shared_ptr<Resource> r2 = std::make_shared<Journal>("R002", "IEEE Software", "0740-7459");
    std::shared_ptr<Resource> r3 = std::make_shared<Conference>("R003", "Proceedings of OOPSLA", "OOPSLA");

    std::shared_ptr<Person> p1 = std::make_shared<Student>(1001, "Alice Chen");
    std::shared_ptr<Person> p2 = std::make_shared<Staff>(1002, "Dr Bob Smith");
    std::shared_ptr<Person> p3 = std::make_shared<LibStaff>(1003, "Carla Jones");

    std::cout << "--- Resources ---\n";
    std::cout << *r1 << '\n' << *r2 << '\n' << *r3 << "\n\n";

    std::cout << "--- Users ---\n";
    std::cout << *p1 << '\n' << *p2 << '\n' << *p3 << "\n\n";

    std::cout << "Day 1 smoke test complete.\n";
    return 0;
}