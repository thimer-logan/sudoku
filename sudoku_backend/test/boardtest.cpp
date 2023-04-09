#define BOOST_TEST_MODULE BOARD_TEST
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include "Board.h"
#include "Cell.h"


BOOST_AUTO_TEST_CASE(TestInitializeBoard) {
    Board board;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            BOOST_CHECK_EQUAL(0, 0);
            BOOST_CHECK(!board.is_cell_fixed(row, col));
        }
    }
}

BOOST_AUTO_TEST_CASE(TestSetBoard) {
    std::vector<std::shared_ptr<Cell>> board_vector(81);
    for (int i = 0; i < 81; ++i) {
        board_vector[i] = std::make_shared<Cell>(i / 9, i % 9 + 1);
        board_vector[i]->set_value(i % 9 + 1);
    }

    Board board;
    board.set_board(board_vector);
    int index = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            BOOST_CHECK_EQUAL(board.get_cell_value(row, col), index % 9 + 1);
            BOOST_CHECK(!board.is_cell_fixed(row, col));
            ++index;
        }
    }
}

BOOST_AUTO_TEST_CASE(TestSetCellValue) {
    Board board;
    board.set_cell_value(0, 0, 5);
    BOOST_CHECK_EQUAL(board.get_cell_value(0, 0), 5);
}

//BOOST_AUTO_TEST_CASE(TestSetCellFixed) {
//    Board board;
//    board.set_cell_value(0, 0, 5, true);
//    BOOST_CHECK(board.is_cell_fixed(0, 0));
//}

BOOST_AUTO_TEST_CASE(TestClearBoard) {
    Board board;
    board.set_cell_value(0, 0, 5);
    board.clear_board();
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            BOOST_CHECK_EQUAL(board.get_cell_value(row, col), 0);
            BOOST_CHECK(!board.is_cell_fixed(row, col));
        }
    }
}

BOOST_AUTO_TEST_CASE(TestIsValidMove) {
    Board board;
    board.set_cell_value(0, 0, 5);
    BOOST_CHECK(!board.is_valid_move(0, 1, 5)); // Same row
    BOOST_CHECK(!board.is_valid_move(1, 0, 5)); // Same column
    BOOST_CHECK(!board.is_valid_move(1, 1, 5)); // Same square
    BOOST_CHECK(board.is_valid_move(0, 1, 6));
}

BOOST_AUTO_TEST_CASE(TestIsSolved) {
    std::vector<std::vector<int>> board1 = { { 7, 9, 2, 1, 5, 4, 3, 8, 6 },
                                            { 6, 4, 3, 8, 2, 7, 1, 5, 9 },
                                            { 8, 5, 1, 3, 9, 6, 7, 2, 4 },
                                            { 2, 6, 5, 9, 7, 3, 8, 4, 1 },
                                            { 4, 8, 9, 5, 6, 1, 2, 7, 3 },
                                            { 3, 1, 7, 4, 8, 2, 9, 6, 5 },
                                            { 1, 3, 6, 7, 4, 8, 5, 9, 2 },
                                            { 9, 7, 4, 2, 1, 5, 6, 3, 8 },
                                            { 5, 2, 8, 6, 3, 9, 4, 1, 7 } };

    Board real_board(board1);
    BOOST_CHECK(real_board.is_solved());

    std::vector<std::vector<int>> board2 = { { 7, 9, 2, 1, 5, 4, 3, 8, 6 },
                                            { 6, 4, 3, 8, 2, 7, 1, 5, 9 },
                                            { 8, 5, 1, 3, 9, 6, 7, 2, 4 },
                                            { 2, 0, 5, 9, 7, 3, 8, 4, 1 },
                                            { 4, 8, 9, 5, 6, 1, 2, 7, 3 },
                                            { 3, 1, 7, 4, 8, 2, 9, 6, 5 },
                                            { 1, 3, 6, 7, 4, 8, 5, 9, 2 },
                                            { 9, 7, 4, 2, 1, 5, 6, 3, 0 },
                                            { 5, 2, 8, 6, 3, 9, 4, 1, 7 } };

    Board real_board2(board2);
    BOOST_CHECK(!real_board2.is_solved());
}
