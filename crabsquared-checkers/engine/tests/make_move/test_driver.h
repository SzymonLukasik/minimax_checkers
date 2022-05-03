#ifndef CRABSQUARED_CHECKERS_TEST_DRIVER_H
#define CRABSQUARED_CHECKERS_TEST_DRIVER_H
#include <vector>

struct test_data {
  int id;
  board_t board;
  move_t move;
  board_t result;
};

#define TEST(n) {n, board##n, move##n, result##n}

extern const std::vector<test_data> tests;

#endif //CRABSQUARED_CHECKERS_TEST_DRIVER_H
