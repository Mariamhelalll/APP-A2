// LibStaff.cpp
#include "LibStaff.h"
#include <sstream>

// Library staff cannot borrow items — limit is 0.
LibStaff::LibStaff(int id, const std::string& name)
    : Person(id, name, 0) {}

std::string LibStaff::asString() const {
    std::ostringstream oss;
    oss << "[LIBSTAFF] " << _ID << " | " << _name << " (cannot borrow)";
    return oss.str();
}