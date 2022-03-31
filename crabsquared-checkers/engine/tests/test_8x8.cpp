#include <iostream>
#include <sstream>
#include <cassert>

#include "../engine.h"
#include "utils.h"

using namespace std;

// full generality on a 8x8 board
const board_t board0 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, WP, NP, BK, NP, NP, NP},
        {NP, NP, NP, NP, NP, BP, NP, NP},
        {NP, NP, NP, NP, WP, NP, NP, NP},
        {NP, NP, NP, NP, NP, BP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col0 = B;
const std::string result0 = "{E2: [|[|E2, D1|], [|E2, F1|], [|E2, D3|]|], F3: [|[|F3, G2|]|], F5: [|[|F5, D3, B1|]|]}";

struct test_data {
    int id;
    board_t board;
    piece_color_t col;
    std::string result;
};
#define TEST(n) {n, board##n, col##n, result##n}

const test_data tests[] = {
        TEST(0)
};

int main() {
    for (const test_data& test : tests) {
        std::stringstream ss;
        ss << valid_moves(test.board, test.col);
        if (ss.str() != test.result) {
            std::cerr <<
                      "Test " << test.id <<
                      ": expected " << test.result <<
                      " got: " << ss.str() << '\n';
        }
        assert(ss.str() == test.result);
    }
    return 0;
}
