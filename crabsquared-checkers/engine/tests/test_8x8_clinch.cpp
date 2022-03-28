#include <iostream>
#include <sstream>
#include <cassert>

#include "../engine.h"
#include "utils.h"

using namespace std;

// board boundary clinch
const board_t board0 = {
        {NP, BP, NP, BP, NP, BP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, WP},
        {NP, NP, NP, NP, NP, WP, WP, NP},
        {NP, NP, WP, NP, WP, WP, WP, WP}
};
const piece_color_t col0 = B;
const std::string result0 = "{}";

const board_t board1 = board0;
const piece_color_t col1 = W;
const std::string result1 = "{}";

// less trivial clinch
const board_t board2 = {
        {WP, NP, WP, NP, WP, NP, WP, NP},
        {NP, BP, NP, BP, NP, BP, NP, BP},
        {BP, NP, BP, NP, BP, NP, BP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP}
};
const piece_color_t col2 = B;
const std::string result2 = "{}";

const board_t board3 = board2;
const piece_color_t col3 = W;
const std::string result3 = "{}";

// no clinch! kings can move backwards
const board_t board4 = {
        {NP, BK, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP}
};
const piece_color_t col4 = B;
const std::string result4 = "{B1: [|[|B1, A2|], [|B1, C2|]|]}";

struct test_data {
    int id;
    board_t board;
    piece_color_t col;
    std::string result;
};
#define TEST(n) {n, board##n, col##n, result##n}

const test_data tests[] = {
        TEST(0),
        TEST(1),
        TEST(2),
        TEST(3),
        TEST(4)
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
