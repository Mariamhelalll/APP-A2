// =============================================================
// File:       UserList.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// =============================================================
#include "UserList.h"
#include "Student.h"
#include "Staff.h"
#include "LibStaff.h"
#include "StringUtils.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

// Factory: type token -> concrete Person subclass.
std::shared_ptr<Person> UserList::makeUser(
    const std::string& type, int id, const std::string& name)
{
    if (type == "STUDENT")  return std::make_shared<Student>(id, name);
    if (type == "STAFF")    return std::make_shared<Staff>(id, name);
    if (type == "LIBSTAFF") return std::make_shared<LibStaff>(id, name);
    return nullptr;
}

UserList::UserList(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error(
            "UserList: could not open file '" + filename + "'");
    }

    std::string line;
    std::size_t lineNo = 0;
    int nextId = 1001;

    while (std::getline(in, line)) {
        ++lineNo;
        if (line.empty() || line.front() == '#') continue;

        // Shared split helper - no more duplication (Day 6 DRY fix).
        auto tokens = StringUtils::split(line, '|');
        if (tokens.size() < 2) {
            std::cerr << "[warn] users.txt line " << lineNo
                      << ": skipping malformed line\n";
            continue;
        }

        const std::string& type = tokens[0];
        const std::string& name = tokens[1];

        auto user = makeUser(type, nextId, name);
        if (!user) {
            std::cerr << "[warn] users.txt line " << lineNo
                      << ": unknown type '" << type << "'\n";
            continue;
        }

        _u_list.push_back(std::move(user));
        ++nextId;
    }
}

void UserList::printUserList() const {
    for (const auto& p : _u_list) {
        std::cout << *p << '\n';
    }
}