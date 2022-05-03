#include <iostream>
#include <sstream>
#include <cassert>
#include "engine.h"
#include "utils.h"
#include "test_driver.h"


int main() {
  for (const test_data& test : tests) {
    board_t output = get_board_after_move(test.board, test.move);
    bool test_passed = (output == test.result);
    if (!test_passed) {
      std::cerr <<
                "Test " << test.id << ":\n" <<
                "expected:\n" << test.result <<
                "got:\n" << output << '\n';
    }
    assert(test_passed);
  }
  return 0;
}
