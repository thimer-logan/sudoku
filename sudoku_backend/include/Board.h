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

    Board(const std::vector<std::vector<int>>& board);

    Board(const std::vector<int>& board);

    Board(std::vector<std::vector<std::shared_ptr<Cell>>> board);

    Board(std::vector<std::shared_ptr<Cell>> board);

    std::vector<std::vector<std::shared_ptr<Cell>>> get_board() const;

    void set_board(const std::vector<std::shared_ptr<Cell>>& board);

    void set_board(const std::vector<std::vector<std::shared_ptr<Cell>>>& board);

    void print_board() const;

    int get_cell_value(int row, int col) const;

    void set_cell_value(int row, int col, int value, bool fixed=false);

    void reset_cell_value(int row, int col);

    bool is_cell_fixed(int row, int col) const;

    bool is_solved() const;

    bool is_valid_move(int row, int col, int value);

    void clear_board();

    int get_width() const;

private:
    const std::set<int> _valid_values {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::vector<std::shared_ptr<Cell>>> _board;

    void initialize_board();

    bool is_row_valid(int row) const;
    bool is_column_valid(int col) const;
    bool is_square_valid(int row, int col) const;

};