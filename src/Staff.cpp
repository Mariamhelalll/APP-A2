// Staff.cpp
#include "Staff.h"
#include <sstream>

Staff::Staff(int id, const std::string& name)
    : Person(id, name, 2) {}

std::string Staff::asString() const {
    std::ostringstream oss;
    oss << "[STAFF]    " << _ID << " | " << _name
        << " (loans: " << _currentLoans << "/" << _borrow_limit << ")";
    return oss.str();
}