// Conference.h
#pragma once

#include "Resource.h"

class Conference : public Resource {
private:
    std::string _acronym;   // e.g. "OOPSLA", "ICSE"

public:
    Conference(const std::string& id, const std::string& title, const std::string& acronym);
    std::string asString() const override;

    const std::string& getAcronym() const { return _acronym; }
};