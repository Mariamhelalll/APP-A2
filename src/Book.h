// =============================================================
// File:       Book.h
// =============================================================
#pragma once
#include "Resource.h"

/**
 * @class Book
 * @brief A lendable book with an author field.
 */
class Book final : public Resource {
private:
    std::string _author;

public:
    Book(const std::string& id, const std::string& title, const std::string& author);
    std::string asString() const override;
    const std::string& getAuthor() const { return _author; }
};