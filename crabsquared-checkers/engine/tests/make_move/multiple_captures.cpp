#include <string>
#include "engine.h"
#include "test_driver.h"

using namespace std;

// multiple captures - big loop
const board_t board0 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BK, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, BP, NP, BP, NP, NP, NP, NP},
        {WK, NP, NP, NP, NP, NP, NP, NP},
};

const move_t move0 = {{7, 0}, {5, 2}, {3, 4}, {1, 2}, {3, 0}, {5, 2}, {7, 4}};

const board_t result0 = {
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, NP, NP, NP, NP},
        {NP, NP, NP, NP, WK, NP, NP, NP},
};

const std::vector<test_data> tests = {
        TEST(0)
};

