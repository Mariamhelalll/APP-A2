// UserList.cpp
#include "UserList.h"
#include <iostream>

UserList::UserList(const std::string& filename) {
    // TODO Day 2: parse file, create Student/Staff/LibStaff via factory.
    (void)filename;
}

void UserList::printUserList() const {
    for (const auto& p : _u_list) {
        std::cout << *p << '\n';
    }
}