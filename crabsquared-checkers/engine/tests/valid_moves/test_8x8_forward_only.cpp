#include <string>
#include "engine.h"
#include "utils.h"
#include "test_driver.h"

using namespace std;

// empty board
const board_t board0 = {
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP},
    {NP, NP, NP, NP, NP, NP, NP, NP}
};
const piece_color_t col0 = B;
const std::string result0 = "{}";

const board_t board1 = board0;
const piece_color_t col1 = W;
const std::string result1 = "{}";

const board_t board2 = board0;
// N color - illegal
//const piece_color_t col2 = N; 
const std::string result2 = "{}";


// single white pawn
const board_t board3 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, WP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP}
};
const piece_color_t col3 = B;
const std::string result3 = "{}";

const board_t board4 = board3;
const piece_color_t col4 = W;
const std::string result4 = "{B3: [|[|B3, A4|], [|B3, C4|]|]}";

// single black pawn
const board_t board5 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, BP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP}
};
const piece_color_t col5 = B;
const std::string result5 = "{C2: [|[|C2, B1|], [|C2, D1|]|]}";

const board_t board6 = board5;
const piece_color_t col6 = W;
const std::string result6 = "{}";

const std::vector<test_data> tests = {
        TEST(0),
        TEST(1),
//        TEST(2),
        TEST(3),
        TEST(4),
        TEST(5),
        TEST(6)
};
