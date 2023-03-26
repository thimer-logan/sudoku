#pragma once

#include "Cell.h"
#include <vector>
#include <memory>
#include <deque>
#include <set>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>

class Board {

public:
    Board();

    std::vector<std::vector<std::shared_ptr<Cell>>> get_board();

    void print_board() const;

    int get_cell_value(int row, int col) const;

    void set_cell_value(int row, int col, int value, bool fixed=false);

    bool is_cell_fixed(int row, int col) const;

    bool is_solved() const;

    bool is_valid_move(int row, int col, int value) const;

    void clear_board();

private:
    const std::set<int> _valid_values {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::vector<std::shared_ptr<Cell>>> _board;

    void initialize_board();

    bool is_row_valid(int row) const;
    bool is_column_valid(int col) const;
    bool is_square_valid(int row, int col) const;

};