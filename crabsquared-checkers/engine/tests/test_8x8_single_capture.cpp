#include <iostream>
#include <sstream>
#include <cassert>

#include "../engine.h"
#include "utils.h"

using namespace std;

// no capture (too far)
const board_t board0 = {
        {NP, WP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, BP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col0 = B;
const std::string result0 = "{D3: [|[|D3, C2|], [|D3, E2|]|]}";

const board_t board1 = board0;
const piece_color_t col1 = W;
const std::string result1 = "{B1: [|[|B1, A2|], [|B1, C2|]|]}";


// single capture
const board_t board2 = {
        {NP, WP, NP, NP, NP, NP, NP, NP},
        {NP, NP, BP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col2 = B;
const std::string result2 = "{C2: [|[|C2, D1|]|]}";

// CAPTURE IS OBLIGATORY!
const board_t board3 = board2;
const piece_color_t col3 = W;
const std::string result3 = "{B1: [|[|B1, D3|]|]}";


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
        TEST(3)
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
