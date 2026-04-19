// Person.cpp
#include "Person.h"

Person::Person(int id, const std::string& name, int borrowLimit)
    : _borrow_limit(borrowLimit), _ID(id), _name(name), _currentLoans(0) {}