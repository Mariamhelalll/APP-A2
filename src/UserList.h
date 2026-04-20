// =============================================================
// File:       UserList.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Owns the master list of system users. Loads them
//             from a pipe-delimited text file using a factory.
// =============================================================
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Person.h"

class UserList {
private:
    std::vector<std::shared_ptr<Person>> _u_list;

    // Factory helper for users. One place for the type decision.
    static std::shared_ptr<Person> makeUser(
        const std::string& type,
        int id,
        const std::string& name);

public:
    // Loads users from a pipe-delimited text file.
    // Throws std::runtime_error if the file cannot be opened.
    explicit UserList(const std::string& filename);

    // Prints every user polymorphically.
    void printUserList() const;

    // Read-only access for reports and borrow lookups.
    const std::vector<std::shared_ptr<Person>>& getAll() const { return _u_list; }
};