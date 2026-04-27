// File:       UserList.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:   - Declares the UserList class, which manages the collection of users in the library.

#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Person.h"
// The UserList class manages the collection of users in the library.
// It is responsible for loading users from a file, creating the appropriate Person objects based on the type specified in the file, and providing access to the list of users for reporting and searching purposes.
//   The class includes a factory method for creating Person objects from parsed data, and it handles errors in the input file by throwing exceptions.
class UserList {
private:
    std::vector<std::shared_ptr<Person>> _u_list;

    // Factory: type token = concrete Person subclass. Adding a new Person type = one new branch here.
    static std::shared_ptr<Person> makeUser(
        const std::string& type,
        int id,
        const std::string& name);
        
// The makeUser function is a factory helper that takes a type token (eg: "STUDENT", "STAFF", "LIBSTAFF"), an ID, and a name.
// It creates and returns a shared pointer to the appropriate Person subclass based on the type token. 
// If the type is unknown, it returns nullptr. This function is used by the UserList
public:
    // Loads users from a pipe-delimited text file.
    // Throws std::runtime_error if the file cannot be opened.
    explicit UserList(const std::string& filename);

    // Prints every user polymorphically.
    void printUserList() const;

    // Read-only access for reports and borrow lookups.
    const std::vector<std::shared_ptr<Person>>& getAll() const { return _u_list; }
};