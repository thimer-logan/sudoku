#pragma once

#include "Cell.h"
#include <vector>
#include <memory>
#include <deque>
#include <set>
#include <algorithm>
#include <random>

class Generator {

public:
    std::vector<std::shared_ptr<Cell>> generate_board();

private:
    const std::set<int> _valid_values {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<std::shared_ptr<Cell>> _board;

    bool fill_bactrack(std::deque<std::shared_ptr<Cell>> cells);
};