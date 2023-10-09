#include "Board.h"

Board::Board() {
    initialize_board();
}

Board::Board(const std::vector<std::vector<int>>& board) {
    if (board.size() != 9 || board[0].size() != 9) {
        throw std::invalid_argument("Invalid board size. The input board must have 9x9 cells.");
    }

    for (int i = 0; i < 9; i++) {
        std::vector<std::shared_ptr<Cell>> row;
        for (int j = 0; j < 9; j++) {
            row.push_back(std::make_shared<Cell>(i, j, board[i][j]));
        }

        _board.push_back(row);
    }
}

Board::Board(const std::vector<int>& board) {
    if (board.size() != 81) {
        throw std::invalid_argument("Invalid board size. The input board must have 81 cells.");
    }

    int index = 0;
    for (int i = 0; i < 9; i++) {
        std::vector<std::shared_ptr<Cell>> row;
        for (int j = 0; j < 9; j++) {
            row.push_back(std::make_shared<Cell>(i, j, board[index]));
            index++;
        }

        _board.push_back(row);
    }
}

Board::Board(std::vector<std::vector<std::shared_ptr<Cell>>> board) {
    initialize_board();
    set_board(board);
}

Board::Board(std::vector<std::shared_ptr<Cell>> board) {
    initialize_board();
    set_board(board);
}

std::vector<std::vector<std::shared_ptr<Cell>>> Board::get_board() const {
    return _board;
}

void Board::set_board(const std::vector<std::shared_ptr<Cell>>& board) {
    // Check if the input board has the correct size (81 cells)
    if (board.size() != 81) {
        throw std::invalid_argument("Invalid board size. The input board must have 81 cells.");
    }

    // Convert the 1D vector of cells to a 9x9 2D vector of cells
    int index = 0;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            _board[row][col] = board[index];
            ++index;
        }
    }
}

void Board::set_board(const std::vector<std::vector<std::shared_ptr<Cell>>>& board) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            _board[row][col] = board[row][col];
        }
    }
}

void Board::print_board() const {
    int r = 1;
    for (auto row : _board) {
        int c = 1;
        for (auto cell : row) {
            std::cout << (cell->get_value() == 0 ? " ": std::to_string(cell->get_value())) << (c % 3 || c==9? " ": " | ");
            c++;
        }
        std::cout << "\n";

        if (r % 3 == 0 && r != 9) {
            std::cout << "---------------------\n";
        }

        r++;
    }
}

int Board::get_cell_value(int row, int col) const {
    if (row < 0 && row > 8) {
        std::string msg = "Invalid row value of " + std::to_string(row) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    if (col < 0 && col > 8) {
        std::string msg = "Invalid column value of " + std::to_string(col) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    return _board[row][col]->get_value();
}

void Board::set_cell_value(int row, int col, int value, bool fixed) {
    if (row < 0 || row > 8) {
        std::string msg = "Invalid row value of " + std::to_string(row) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    if (col < 0 || col > 8) {
        std::string msg = "Invalid column value of " + std::to_string(col) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }

    if (_valid_values.find(value) == _valid_values.end()) {
        std::string msg = "Invalid cell value of " + std::to_string(value) + ". Must be between 1 and 9 inclusive";
        throw std::invalid_argument(msg);
    }

    _board[row][col]->set_value(value);
}

void Board::reset_cell_value(int row, int col) {
    if (row < 0 || row > 8) {
        std::string msg = "Invalid row value of " + std::to_string(row) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg);
    }

    if (col < 0 || col > 8) {
        std::string msg = "Invalid column value of " + std::to_string(col) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg);
    }

    _board[row][col]->set_value(0);
}

bool Board::is_cell_fixed(int row, int col) const {
    return false;
}

bool Board::is_solved() const {
    for (int i = 0; i < 9; i++) {
        if (!is_row_valid(i) || !is_column_valid(i)) {
            return false;
        }
        for (int j = 0; j < 9; j++) {
            if (_board[i][j]->get_value() == 0) {
                return false;
            }
        }
    }

    for (int i = 0; i < 9; i+=3) {
        for (int j = 0; j < 9; j+=3) {
            if (!is_square_valid(i, j)) {
                return false;
            }
        }
    }

    return true;
}

bool Board::is_valid_move(int row, int col, int value) {
    int old = get_cell_value(row, col);
    _board[row][col]->set_value(value);

    if (is_row_valid(row) && is_column_valid(col) && is_square_valid(row, col)) {
        _board[row][col]->set_value(old);
        return true;
    }
    else {
        _board[row][col]->set_value(old);
        return false;
    }

}

void Board::clear_board() {
    for (auto row : _board) {
        for (auto cell : row) {
            cell->set_value(0);
        }
    }
}

int Board::get_width() const
{
    return 9;
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
    if (row < 0 || row > 8) {
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
    if (col < 0 || col > 8) {
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
    if (row < 0 || row > 8) {
        std::string msg = "Invalid row value of " + std::to_string(row) + ". Must be between 0 and 8 inclusive";
        throw std::invalid_argument(msg); 
    }
    
    if (col < 0 || col > 8) {
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

