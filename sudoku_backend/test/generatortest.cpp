#define BOOST_TEST_MODULE GENERATOR_TEST
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include "Generator.h"
#include "Board.h"


BOOST_AUTO_TEST_CASE(TestValidGeneration) {
    Generator gen;
    Board board(gen.generate_board());

    BOOST_CHECK(board.is_solved());
}

BOOST_AUTO_TEST_CASE(TestRemoveValuesEasy) {
    Generator gen;
    Board board(gen.generate_board());
    gen.remove_values(board, EASY);

    BOOST_CHECK(!board.is_solved());
}

BOOST_AUTO_TEST_CASE(TestRemoveValuesMedium) {
    Generator gen;
    Board board(gen.generate_board());
    gen.remove_values(board, MEDIUM);

    BOOST_CHECK(!board.is_solved());
}

BOOST_AUTO_TEST_CASE(TestRemoveValuesHard) {
    Generator gen;
    Board board(gen.generate_board());
    gen.remove_values(board, HARD);

    BOOST_CHECK(!board.is_solved());
}