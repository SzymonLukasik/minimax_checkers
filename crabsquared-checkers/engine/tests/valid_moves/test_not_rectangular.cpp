#include <string>
#include "engine.h"
#include "utils.h"
#include "test_driver.h"

using namespace std;

const board_t board0 = {
  {NP, NP, BK, NP, NP},
  {NP, WK, WP, NP, NP},
  {NP, NP, NP, BP, NP},
};
const piece_color_t col0 = B;
const std::string result0 = "{C1: [|[|C1, A3|]|], D3: [|[|D3, B1|]|]}";


const std::vector<test_data> tests = {
  TEST(0)
};
