#include "Generator.h"

Generator::Generator() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            _board.push_back(std::make_shared<Cell>(i, j));
        }
    }
}

std::vector<std::shared_ptr<Cell>> Generator::generate_board() {
    auto cells = std::deque<std::shared_ptr<Cell>> (_board.begin(), _board.end());

    if (!fill_backtrack(cells)) {
        std::cout << "Could not generate board" << std::endl;
    }

    return _board;
}

void Generator::remove_values(Board& board, Difficulty difficulty) const {
    int num_cells_to_remove;
    int board_size = 9 * 9;

    switch (difficulty) {
        case EASY:
            num_cells_to_remove = board_size / 4; // Remove 25% of the cells
            break;
        case MEDIUM:
            num_cells_to_remove = board_size / 2; // Remove 50% of the cells
            break;
        case HARD:
            num_cells_to_remove = (3 * board_size) / 4; // Remove 75% of the cells
            break;
        case EXTREME:
            num_cells_to_remove = (8 * board_size) / 10; // Remove 80% of the cells
            break;
        default:
            throw std::invalid_argument("Invalid difficulty");
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < num_cells_to_remove; ++i) {
        std::uniform_int_distribution<> row_dist(0, 8);
        std::uniform_int_distribution<> col_dist(0, 8);

        int row = row_dist(gen);
        int col = col_dist(gen);

        // Ensure that the cell is not already removed
        while (board.get_cell_value(row, col) == 0) {
            row = row_dist(gen);
            col = col_dist(gen);
        }

        // Remove the value from the cell
        board.reset_cell_value(row, col);
    }
}

void Generator::remove_values(std::vector<std::shared_ptr<Cell>>& board, Difficulty difficulty) const {
    int num_cells_to_remove;
    int board_size = 9 * 9;

    switch (difficulty) {
    case EASY:
        num_cells_to_remove = board_size / 4; // Remove 25% of the cells
        break;
    case MEDIUM:
        num_cells_to_remove = board_size / 2; // Remove 50% of the cells
        break;
    case HARD:
        num_cells_to_remove = (3 * board_size) / 4; // Remove 75% of the cells
        break;
    case EXTREME:
        num_cells_to_remove = (8 * board_size) / 10; // Remove 80% of the cells
        break;
    default:
        throw std::invalid_argument("Invalid difficulty");
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < num_cells_to_remove; ++i) {
        std::uniform_int_distribution<> row_dist(0, 8);
        std::uniform_int_distribution<> col_dist(0, 8);

        int row = row_dist(gen);
        int col = col_dist(gen);

        // Ensure that the cell is not already removed
        while (board[9*row+col] == 0) {
            row = row_dist(gen);
            col = col_dist(gen);
        }

        // Remove the value from the cell
        board[9 * row + col] = 0;
    }
}

bool Generator::fill_backtrack(std::deque<std::shared_ptr<Cell>>& cells) {
    auto cell = cells.front();
    cells.pop_front();

    std::set<int> neighbours = {};

    for (auto& neighbour : cell->get_neighbours()) {
        // have to use 1D point
        neighbours.insert(_board[9 * neighbour.x + neighbour.y]->get_value());
    }

    std::vector<int> options;
    std::set_difference(_valid_values.begin(), _valid_values.end(),
        neighbours.begin(), neighbours.end(),
        std::inserter(options, options.begin())
    );

    std::random_device rd;
    auto rng = std::default_random_engine{ rd() };
    std::shuffle(std::begin(options), std::end(options), rng);

    for (auto option : options) {
        cell->set_value(option);

        if (cells.empty()) {
            return true;
        }

        if (fill_backtrack(cells)) {
            return true;
        };
    }

    cell->set_value(0);
    cells.push_front(cell);

    return false;
}