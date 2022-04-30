#ifndef CRABSQUARED_CHECKERS_UTILS_H
#define CRABSQUARED_CHECKERS_UTILS_H

#include <iostream>
#include "engine.h"

#define TEST(n) {n, board##n, col##n, result##n}

struct test_data {
  int id;
  board_t board;
  piece_color_t col;
  std::string result;
};

/*
    Converts pos to square name.
    Eg: (1,2) -> "C2"
        (3,5) -> "F4"
*/
inline std::string sqtostr(square_t sq)
{
    return {char(sq.second + char('A')), char(sq.first + char('1'))};
}

inline std::ostream &operator<<(std::ostream &os, square_t sq)
{
    os << sqtostr(sq);
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::list<T>& x) {
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

//template <typename U, typename V>
//std::ostream& operator<< (std::ostream& os, const std::pair<U, V>& x) {
//    os << '<' << x.first << ", " << x.second << '>';
//    return os;
//}

template <typename U, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<U, V>& x)
{
    os << '{';
    if (x.size() > 0) {
        for (auto it=x.begin(); it != std::prev(x.end()); ++it) {
            os << it->first << ": " << it->second << ", ";
        }
        auto it = std::prev(x.end());
        os << it->first << ": " << it->second;
    }
    os << '}';
    return os;
}

//std::ostream &operator<<(std::ostream &os, board_t board)
//{
//  for (size_t i = 0; i < board.size(); i++)
//  {
//    for (size_t j = 0; j < board[0].size(); j++)
//    {
//      os << board[i][j];
//    }
//    os << "\n";
//  }
//  return os;
//}

#endif //CRABSQUARED_CHECKERS_UTILS_H
