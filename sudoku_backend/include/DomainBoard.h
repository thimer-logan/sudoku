#pragma once

#include <vector>
#include <memory>
#include <deque>
#include <set>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <string>
#include "Board.h"

class DomainBoard {

public:
    DomainBoard();

    DomainBoard(const Board& board);

    DomainBoard(const std::vector<std::vector<int>>& board);

    //DomainBoard(const std::vector<int>& board);

    //DomainBoard(std::vector<std::vector<std::set<int>>> board);

    //DomainBoard(std::vector<std::set<int>> board);

    Board to_board() const;

    std::vector<std::vector<std::set<int>>> get_board() const;

    //void set_board(const std::vector<std::set<int>>& board);

    void set_board(const std::vector<std::vector<std::set<int>>>& board);

    void print_board() const;

    std::set<int> get_cell_domain(const Cell& cell) const;

    std::set<int> get_cell_domain(int row, int col) const;

    void set_cell_domain(const std::set<int>& domain, const Cell& cell);

    void set_cell_domain(const std::set<int>& domain, int row, int col);

    bool is_solved() const;

    bool is_valid_move(const Cell& cell, int value) const;

    bool is_valid_move(int row, int col, int value) const;

    void clear_board();

    int get_width() const;

private:
    const std::set<int> _valid_values{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector<std::vector<std::set<int>>> _board;

    void initialize_board();

    bool is_row_valid(int row) const;
    bool is_column_valid(int col) const;
    bool is_square_valid(int row, int col) const;

    void printCell(const std::set<int>& domain, int row) const;
    void printThinSeparator() const;
    void printThickSeparator() const;

};