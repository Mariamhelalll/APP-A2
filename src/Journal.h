// =============================================================
// File:       Journal.h
// =============================================================
#pragma once
#include "Resource.h"

/**
 * @class Journal
 * @brief A lendable periodical identified by its ISSN.
 */
class Journal final : public Resource {
private:
    std::string _issn;   ///< International Standard Serial Number

public:
    Journal(const std::string& id, const std::string& title, const std::string& issn);
    std::string asString() const override;
    const std::string& getISSN() const { return _issn; }
};