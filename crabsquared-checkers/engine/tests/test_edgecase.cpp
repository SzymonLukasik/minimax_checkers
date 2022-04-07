#include <string>
#include "engine.h"
#include "tests/utils.h"
#include "tests/test_driver.h"

using namespace std;

const board_t board0 = {
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
  {NP, NP, NP, NP, NP, NP, NP, NP},
};
const piece_color_t col0 = B;
const std::string result0 = "{}";

const board_t board1 = board0;
const piece_color_t col1 = W;
const std::string result1 = "{}";

const board_t board2 = {};
const piece_color_t col2 = W;
const std::string result2 = "{}";

const board_t board3 = {};
const piece_color_t col3 = B;
const std::string result3 = "{}";


const std::vector<test_data> tests = {
  TEST(0),
  TEST(1),
  TEST(2)
};
