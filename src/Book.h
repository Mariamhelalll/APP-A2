// Book.h
#pragma once

#include "Resource.h"

class Book : public Resource {
private:
    std::string _author;

public:
    Book(const std::string& id, const std::string& title, const std::string& author);

    // override keyword: compiler catches typos in the signature
    std::string asString() const override;

    const std::string& getAuthor() const { return _author; }
};