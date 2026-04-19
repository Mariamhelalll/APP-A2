// ResourceList.cpp
#include "ResourceList.h"
#include <iostream>

ResourceList::ResourceList(const std::string& filename) {
    // TODO Day 2: parse the file, create Book/Journal/Conference via factory.
    (void)filename;  // silence unused-parameter warning for now
}

void ResourceList::printResourceList() const {
    for (const auto& r : _r_list) {
        std::cout << *r << '\n';
    }
}