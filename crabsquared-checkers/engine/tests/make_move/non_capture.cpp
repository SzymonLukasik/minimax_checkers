#include <string>
#include "engine.h"
#include "test_driver.h"

using namespace std;


// left-forward non-capture
const board_t board0 = {
        {NP, NP, NP},
        {NP, NP, NP},
        {NP, WP, NP}
};

const move_t move0 = {{2, 1}, {1, 0}};

const board_t result0 = {
        {NP, NP, NP},
        {WP, NP, NP},
        {NP, NP, NP} 
};


// right-forward non-capture
const board_t board1 = {
        {NP, NP, NP},
        {NP, NP, NP},
        {NP, BK, NP}
};

const move_t move1 = {{2, 1}, {1, 2}};

const board_t result1 = {
        {NP, NP, NP},
        {NP, NP, BK},
        {NP, NP, NP} 
};


// left-backward non-capture
const board_t board2 = {
        {NP, BP, NP},
        {NP, NP, NP},
        {NP, NP, NP}
};

const move_t move2 = {{0, 1}, {1, 0}};

const board_t result2 = {
        {NP, NP, NP},
        {BP, NP, NP},
        {NP, NP, NP} 
};


// right-backward non-capture
const board_t board3 = {
        {NP, WK, NP},
        {NP, NP, NP},
        {NP, NP, NP}
};

const move_t move3 = {{0, 1}, {1, 2}};

const board_t result3 = {
        {NP, NP, NP},
        {NP, NP, WK},
        {NP, NP, NP} 
};

const std::vector<test_data> tests = {
        TEST(0),
        TEST(1),
        TEST(2),
        TEST(3)
};
