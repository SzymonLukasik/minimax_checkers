#include <string>
#include "engine.h"
#include "utils.h"
#include "test_driver.h"

using namespace std;


// left-forward single capture
const board_t board0 = {
        {NP, NP, NP},
        {NP, BP, NP},
        {NP, NP, WP}
};

const move_t move0 = {{2, 2}, {0, 0}};

const board_t result0 = {
        {WP, NP, NP},
        {NP, NP, NP},
        {NP, NP, NP} 
};


// right-forward single capture
const board_t board1 = {
        {NP, NP, NP},
        {NP, WP, NP},
        {BK, NP, NP}
};

const move_t move1 = {{2, 0}, {0, 2}};

const board_t result1 = {
        {NP, NP, BK},
        {NP, NP, NP},
        {NP, NP, NP} 
};


// left-backward single capture
const board_t board2 = {
        {NP, NP, BP},
        {NP, WP, NP},
        {NP, NP, NP}
};

const move_t move2 = {{0, 2}, {2, 0}};

const board_t result2 = {
        {NP, NP, NP},
        {NP, NP, NP},
        {BP, NP, NP} 
};


// right-backward single capture
const board_t board3 = {
        {WK, NP, NP},
        {NP, BP, NP},
        {NP, NP, NP}
};

const move_t move3 = {{0, 0}, {2, 2}};

const board_t result3 = {
        {NP, NP, NP},
        {NP, NP, NP},
        {NP, NP, WK} 
};

const std::vector<test_data> tests = {
        TEST(0),
        TEST(1),
        TEST(2),
        TEST(3)
};

