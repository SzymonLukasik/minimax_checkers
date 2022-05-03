#include <string>
#include "engine.h"
#include "test_driver.h"

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

// capture is obligatory, but the player can choose which capturing to do
const board_t board4 = {
        {NP, NP, WP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col4 = W;
const std::string result4 = "{C1: [|[|C1, A3|], [|C1, E3|]|]}";

const std::vector<test_data> tests = {
        TEST(0),
        TEST(1),
        TEST(2),
        TEST(3),
        TEST(4)
};
