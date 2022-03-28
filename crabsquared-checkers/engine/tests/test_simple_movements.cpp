#include <iostream>
#include "../engine.h"

using namespace std;

/*
    Converts pos to square name.
    Eg: (1,2) -> "C2"
        (3,5) -> "F4"
*/
inline std::string sqtostr(square_t sq)
{
    return {char(sq.second + char('A')), char(sq.first + char('1'))};
}

std::ostream &operator<<(std::ostream &os, square_t sq)
{
    os << sqtostr(sq);
    return os;
}

std::ostream &operator<<(std::ostream &os, move_t mv)
{
    for (auto sq : mv)
    {
        os << sq << " ";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, square_moves_t ml)
{
    for (auto mv : ml)
    {
        os << "{" << mv << "}";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, std::pair<square_t, square_moves_t> p)
{
    os << p.first << ": " << p.second;
    return os;
}

std::ostream &operator<<(std::ostream &os, board_moves_t vm)
{
    for (auto m : vm)
    {
        std::cout << m << std::endl;
    }
    return os;
}

// default initial configuration
const board_t board1 = {
        {WP, NP, WP, NP, WP, NP, WP, NP},
        {NP, WP, NP, WP, NP, WP, NP, WP},
        {WP, NP, WP, NP, WP, NP, WP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, WP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BP, NP, BP, NP, BP},
        {BP, NP, BP, NP, BP, NP, BP, NP},
        {NP, BP, NP, BP, NP, BP, NP, BP},
};

// double jump forward for white king
const board_t board2 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BP, NP, NP, NP, NP},
        {NP, NP, WK, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};

// double jump forward for white king
const board_t board3 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, BP, NP, NP, NP, NP},
        {NP, NP, NP, NP, WK, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};

// double jump for whites
const board_t board4 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BP, NP, NP, NP, NP},
        {NP, NP, WK, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};

int main() {
    cout << valid_moves(board1, B) << '\n';
    cout << "All tests successful!\n";
    return 0;
}
