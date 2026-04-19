// Loan.cpp
#include "Loan.h"
#include <sstream>

Loan::Loan(std::shared_ptr<Person> per, std::shared_ptr<Resource> res)
    : _per(std::move(per)), _res(std::move(res)) {}

std::string Loan::asString() const {
    std::ostringstream oss;
    oss << _per->getName() << " <- " << _res->getTitle();
    return oss.str();
}