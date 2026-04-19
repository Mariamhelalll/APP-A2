// UserList.h
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Person.h"

class UserList {
private:
    std::vector<std::shared_ptr<Person>> _u_list;

public:
    UserList(const std::string& filename);
    void printUserList() const;

    const std::vector<std::shared_ptr<Person>>& getAll() const { return _u_list; }
};