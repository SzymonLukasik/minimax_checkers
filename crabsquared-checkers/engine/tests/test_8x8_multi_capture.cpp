#include <iostream>
#include <sstream>
#include <cassert>

#include "../engine.h"
#include "utils.h"

using namespace std;

// obligatory capture
const board_t board0 = {
        {NP, WP, NP, NP, NP, NP, NP, NP},
        {NP, NP, BP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, BP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col0 = W;
const std::string result0 = "{B1: [|[|B1, D3, B5|]|]}";

// ability to choose: pawn cannot capture backwards
const board_t board1 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, BP, NP, NP, NP, NP, NP},
        {NP, NP, NP, WP, NP, NP, NP, NP},
        {NP, NP, NP, NP, BP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, BP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col1 = W;
const std::string result1 = "{D3: [|[|D3, F5, H7|]|]}";

// ability to choose: but kings can!
const board_t board2 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, BP, NP, NP, NP, NP, NP},
        {NP, NP, NP, WK, NP, NP, NP, NP},
        {NP, NP, NP, NP, BP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, BP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col2 = W;
const std::string result2 = "{D3: [|[|D3, B1|], [|D3, F5, H7|]|]}";

// LOOP!
const board_t board3 = {
        {NP, NP, NP, WP, NP, NP, NP, NP},
        {NP, NP, BP, NP, BP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, BP, NP, BP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col3 = W;
const std::string result3 = "{D3: [|[|D1, B3, D5, E3, D1|], [|D1, E3, D5, B3, D1|]|]}";


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
        TEST(2)
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
