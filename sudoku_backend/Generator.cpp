#include "Generator.h"

std::vector<std::shared_ptr<Cell>> Generator::generate_board() {
    auto cells = std::deque<std::shared_ptr<Cell>> (_board.begin(), _board.end());

    if (!fill_bactrack(cells)) {
        std::cout << "Could not generate board" << std::endl;
    }

    return _board;
}

bool Generator::fill_bactrack(std::deque<std::shared_ptr<Cell>> cells) {
    auto cell = cells.front();
    cells.pop_front();

    std::set<int> neighbours = {};

    for(auto &neighbour : cell->get_neighbours()) {
        // have to use 1D point
        neighbours.insert(_board[9*neighbour.x + neighbour.y]->get_value());
    }

    std::vector<int> options;
    std::set_difference(_valid_values.begin(), _valid_values.end(),
                    neighbours.begin(), neighbours.end(),
                    std::inserter(options, options.begin())
    );
    
    std::random_device rd;
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(options), std::end(options), rng);

    for(auto option : options) {
        cell->set_value(option);

        if (cells.empty()) {
            return true;
        }

        if (fill_bactrack(cells)){
            return true;
        };
    }

    cell->set_value(0);
    cells.push_front(cell);

    return false;
}