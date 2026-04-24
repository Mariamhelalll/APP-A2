// =============================================================
// File:       Conference.h
// =============================================================
#pragma once
#include "Resource.h"

/**
 * @class Conference
 * @brief A conference proceedings entry. Reference-only —
 *        _canLend is hard-coded to false in the constructor.
 */
class Conference final : public Resource {
private:
    std::string _acronym;   ///< e.g. "OOPSLA", "ICSE"

public:
    Conference(const std::string& id, const std::string& title, const std::string& acronym);
    std::string asString() const override;
    const std::string& getAcronym() const { return _acronym; }
};