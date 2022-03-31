#include <string>
#include "../engine.h"
#include "utils.h"
#include "test_driver.h"

using namespace std;

// full generality on an 8x8 board
const board_t board0 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, WP, NP, BK, NP, NP, NP},
        {NP, NP, NP, NP, NP, BP, NP, NP},
        {NP, NP, NP, NP, WP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col0 = B;
const std::string result0 = "{E2: [|[|E2, D1|], [|E2, F1|], [|E2, D3|]|], F3: [|[|F3, G2|]|]}";

const board_t board1 = {
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, WP, NP, BK, NP, NP, NP},
  {NP, NP, NP, NP, NP, BP, NP, NP},
  {NP, NP, NP, NP, WP, NP, NP, NP},
  {NP, NP, NP, NP, NP, BP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col1 = B;
const std::string result1 = "{F5: [|[|F5, D3, B1|]|]}";

const std::vector<test_data> tests = {
        TEST(0),
        TEST(1)
};
