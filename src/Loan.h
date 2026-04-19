// Loan.h
#pragma once

#include <memory>
#include "Person.h"
#include "Resource.h"

class Loan {
private:
    std::shared_ptr<Person>   _per;
    std::shared_ptr<Resource> _res;

public:
    Loan(std::shared_ptr<Person> per, std::shared_ptr<Resource> res);

    std::shared_ptr<Person>   getPerson()   const { return _per; }
    std::shared_ptr<Resource> getResource() const { return _res; }

    std::string asString() const;
};