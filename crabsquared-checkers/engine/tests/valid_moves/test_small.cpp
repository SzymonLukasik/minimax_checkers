#include <string>
#include "engine.h"
#include "utils.h"
#include "test_driver.h"

using namespace std;

const board_t board0 = {
  {NP, NP, BK},
  {NP, WK, NP},
  {NP, NP, NP},
};
const piece_color_t col0 = B;
const std::string result0 = "{C1: [|[|C1, A3|]|]}";


const std::vector<test_data> tests = {
  TEST(0)
};
