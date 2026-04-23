// =============================================================
// File:       StringUtils.h
// Author:     Maryam Mohamed
// Student ID: 29073094
// Module:     CMP2811 Applied Programming Paradigms
// Assignment: Assessment Item 2
// Purpose:    Small header-only string helpers used across the
//             project. Currently provides case-insensitive
//             substring matching for the keyword-search feature.
// =============================================================
#pragma once

#include <algorithm>
#include <cctype>
#include <string>

namespace StringUtils {

    // Case-insensitive substring search. Returns true if
    // `needle` appears anywhere inside `haystack`, ignoring case.
    inline bool containsIgnoreCase(const std::string& haystack,
                                   const std::string& needle)
    {
        if (needle.empty()) return true;
        const auto it = std::search(
            haystack.begin(), haystack.end(),
            needle.begin(),   needle.end(),
            [](char a, char b) {
                return std::tolower(static_cast<unsigned char>(a)) ==
                       std::tolower(static_cast<unsigned char>(b));
            });
        return it != haystack.end();
    }

}  // namespace StringUtils