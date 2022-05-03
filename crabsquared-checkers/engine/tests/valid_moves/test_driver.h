#ifndef CRABSQUARED_CHECKERS_TEST_DRIVER_H
#define CRABSQUARED_CHECKERS_TEST_DRIVER_H
#include <vector>

struct test_data {
  int id;
  board_t board;
  piece_color_t col;
  std::string result;
};

#define TEST(n) {n, board##n, col##n, result##n}

extern const std::vector<test_data> tests;

#endif //CRABSQUARED_CHECKERS_TEST_DRIVER_H
