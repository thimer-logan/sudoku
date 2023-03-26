#include "Board.h"

Board::Board() {
    initialize_board();
}

std::vector<std::vector<std::shared_ptr<Cell>>> Board::get_board() {
    return _board;
}

void Board::print_board() const {
    for (auto row : _board) {
        std::cout << "| ";
        for (auto cell : row) {
            std::cout << cell->get_value() << " | ";
        }
        std::cout << "\n";
        std::cout << "____________________________________\n";
    }
}

int Board::get_cell_value(int row, int col) const {
    return _board[row][col]->get_value();
}

void Board::set_cell_value(int row, int col, int value, bool fixed=false) {
    if (row < 0 && row > 8) {
        std::string msg = "Invalid row value of " + std::to_string(row) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    if (col < 0 && col > 8) {
        std::string msg = "Invalid column value of " + std::to_string(col) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    if (_valid_values.find(value) == _valid_values.end()) {
        std::string msg = "Invalid cell value of " + std::to_string(col) + ". Must be between 1 and 9 inclusive";
        throw std::invalid_argument(msg);
    }

    _board[row][col]->set_value(value);
}

bool Board::is_cell_fixed(int row, int col) const {

}

bool Board::is_solved() const {

}

bool Board::is_valid_move(int row, int col, int value) const {

}

void Board::clear_board() {
    for (auto row : _board) {
        for (auto cell : row) {
            cell->set_value(0);
        }
    }
}

void Board::initialize_board() {
    for (int i = 0; i < 9; i++) {
        std::vector<std::shared_ptr<Cell>> row;
        for (int j = 0; j < 9; j++) {
            row.push_back(std::make_shared<Cell>(i, j));
        }

        _board.push_back(row);
    }
}

bool Board::is_row_valid(int row) const {
    if (row < 0 && row > 8) {
        std::string msg = "Invalid row value of " + std::to_string(row) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    std::set<int> values;
    int zeros = 0;
    for (auto cell : _board[row]) {
        if (cell->get_value() == 0) {
            zeros++;
        }
        else {
            values.insert(cell->get_value());
        }
        
    }

    return values.size() + zeros == 9;
}

bool Board::is_column_valid(int col) const {
    if (col < 0 && col > 8) {
        std::string msg = "Invalid column value of " + std::to_string(col) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    std::set<int> values;
    int zeros = 0;
    for (auto row : _board) {
        if (row[col]->get_value() == 0) {
            zeros++;
        }
        else {
            values.insert(row[col]->get_value());
        }        
    }

    return values.size() + zeros == 9;
}

bool Board::is_square_valid(int row, int col) const {
    if (row < 0 && row > 8) {
        std::string msg = "Invalid row value of " + std::to_string(row) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }
    
    if (col < 0 && col > 8) {
        std::string msg = "Invalid column value of " + std::to_string(col) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    auto row_start = (row / 3) * 3;
    auto col_start = (col / 3) * 3;

    std::set<int> values;
    int zeros = 0;
    for (int i = row_start; i < row_start + 3; ++i) {
        for (int j = col_start; j < col_start + 3; ++j) {
            if (_board[i][j]->get_value() == 0) {
                zeros++;
            }
            else {
                values.insert(_board[i][j]->get_value());
            }            
        }
    }

    return values.size() + zeros == 9;
}

