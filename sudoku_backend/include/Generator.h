#pragma once

#include "Cell.h"
#include "Board.h"
#include <vector>
#include <memory>
#include <deque>
#include <set>
#include <algorithm>
#include <random>

enum Difficulty {
    EASY,
    MEDIUM,
    HARD,
    EXTREME
};

class Generator {

public:
    Generator();

    std::vector<std::shared_ptr<Cell>> generate_board();

    void remove_values(Board& board, Difficulty difficulty) const;

    void remove_values(std::vector<std::shared_ptr<Cell>>& board, Difficulty difficulty) const;

private:
    const std::set<int> _valid_values {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::shared_ptr<Cell>> _board;
    std::random_device _rd;
    std::default_random_engine _rng;
    std::vector<int> _options;
    std::set<int> _neighbours;

    bool fill_backtrack(std::deque<std::shared_ptr<Cell>>& cells);
};