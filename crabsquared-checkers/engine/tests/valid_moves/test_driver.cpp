#include <iostream>
#include <sstream>
#include <cassert>
#include "engine.h"
#include "utils.h"
#include "test_driver.h"

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
