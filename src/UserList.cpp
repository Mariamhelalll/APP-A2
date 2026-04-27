// File:       UserList.cpp
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2 - Library Management System
// Purpose:    - Implements the UserList class, which manages the collection of users in the library.
//             - The UserList is responsible for loading users from a file, creating the appropriate Person objects based on the type specified in the file, and providing access to the list of users for reporting and searching purposes.
//             - It includes a factory method for creating Person objects from parsed data, and it handles errors in the input file by throwing exceptions.

#include "UserList.h"
#include "Student.h"
#include "Staff.h"
#include "LibStaff.h"
#include "StringUtils.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

// The makeUser function is a factory helper that takes a type token (eg: "STUDENT", "STAFF", "LIBSTAFF"), an ID, and a name.
// It creates and returns a shared pointer to the appropriate Person subclass based on the type token. 
// If the type is unknown, it returns nullptr. This function is used by the UserList constructor when loading users from the file to create the correct Person objects based on the data provided.
std::shared_ptr<Person> UserList::makeUser(
    const std::string& type, int id, const std::string& name)
{
    if (type == "STUDENT")  return std::make_shared<Student>(id, name);
    if (type == "STAFF")    return std::make_shared<Staff>(id, name);
    if (type == "LIBSTAFF") return std::make_shared<LibStaff>(id, name);
    return nullptr;
}
// The constructor for UserList takes a filename as input and attempts to load users from the specified file.
// It reads the file line by line, skipping empty lines and comments (lines starting with '#'). 
//For each valid line, it splits the line into tokens using the pipe '|' delimiter, extracts the type and name, and uses the makeUser factory function to create the appropriate Person object. 
//If the file cannot be opened, or if there are malformed lines or unknown types, it throws a runtime error or skips the line with a warning.
UserList::UserList(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error(
            "UserList: could not open file '" + filename + "'");
    }

    std::string line;
    std::size_t lineNo = 0;
    int nextId = 1001;

    // Read the file line by line, skipping empty lines and comments (lines starting with '#'). For each valid line, split it into tokens using the pipe '|' delimiter. We expect at least two tokens: the type and the name.
    // If there are fewer than 2 tokens, we consider the line malformed and skip it with a warning. Otherwise, we use the makeUser factory function to create the appropriate Person object based on the type and name. 
    //If the type is unknown, we also skip it with a warning. Valid users are added to the _u_list vector, and each user is assigned a unique ID starting from 1001.
    while (std::getline(in, line)) {
        ++lineNo;
        if (line.empty() || line.front() == '#') continue;

        // Split the line into tokens using the pipe '|' delimiter. We expect at least two tokens: the type and the name. If there are fewer than 2 tokens, we consider the line malformed and skip it with a warning.
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
// The printUserList method iterates through the list of users and prints each one using the overloaded operator<<, which calls the asString method of each Person object to get their string representation for display.
void UserList::printUserList() const {
    for (const auto& p : _u_list) {
        std::cout << *p << '\n';
    }
}