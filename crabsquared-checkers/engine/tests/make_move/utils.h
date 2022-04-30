#ifndef CRABSQUARED_CHECKERS_UTILS_H
#define CRABSQUARED_CHECKERS_UTILS_H

#include <iostream>
#include "engine.h"

#define TEST(n) {n, board##n, move##n, result##n}

struct test_data {
  int id;
  board_t board;
  move_t move;
  board_t result;
};

/*
    Converts piece to piece name.
    Eg: WP -> "WP"
        BK -> "BK"
*/
inline std::string sqtostr(piece_t piece)
{
    switch (piece)
    {
    case piece_t::BK:
        return "BK";
    case piece_t::BP:
        return "BP";
    case piece_t::NP:
        return "NP";
    case piece_t::WK:
        return "WK";
    default: // piece_t::WP:
        return "WP";
    };
}

inline std::ostream &operator<<(std::ostream &os, piece_t piece)
{
    os << sqtostr(piece);
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& x) {
    os << "[|";
    if (!x.empty()) {
        for (auto it=x.begin(); it != std::prev(x.end()); ++it) {
            os << *it << ", ";
        }
        auto it = std::prev(x.end());
        os << *it;
    }
    os << "|]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<T>>& x) {
    if (!x.empty()) {
        for (auto it=x.begin(); it != x.end(); ++it) {
            os << *it << "\n";
        }
    }
    return os;
}

#endif //CRABSQUARED_CHECKERS_UTILS_H
