// ResourceList.h
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Resource.h"

class ResourceList {
private:
    std::vector<std::shared_ptr<Resource>> _r_list;

public:
    // Loads resources from a pipe-delimited text file (format defined Day 2).
    ResourceList(const std::string& filename);

    // Prints every resource polymorphically.
    void printResourceList() const;

    // Raw access for iteration in main / reports (Day 3+).
    const std::vector<std::shared_ptr<Resource>>& getAll() const { return _r_list; }
};