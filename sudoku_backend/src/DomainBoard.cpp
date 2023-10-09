#include "DomainBoard.h"

DomainBoard::DomainBoard()
{
    initialize_board();
}

DomainBoard::DomainBoard(const Board& board)
{
	for (int i = 0; i < board.get_width(); i++) {
		std::vector<std::set<int>> domain_row;
		for (int j = 0; j < board.get_width(); j++) {
			if (board.get_cell_value(i, j) != 0) {
				domain_row.push_back({ board.get_cell_value(i, j) });
			}
			else {
				domain_row.push_back(_valid_values);
			}
		}

		_board.push_back(domain_row);
	}
}

DomainBoard::DomainBoard(const std::vector<std::vector<int>>& board)
{
	for (int i = 0; i < board.size(); i++) {
		std::vector<std::set<int>> domain_row;
		for (int j = 0; j < board.size(); j++) {
			if (board[i][j] != 0) {
				domain_row.push_back({ board[i][j] });
			}
			else {
				domain_row.push_back(_valid_values);
			}
		}

		_board.push_back(domain_row);
	}
}

Board DomainBoard::to_board() const
{
	Board b;
	for (int row = 0; row < get_width(); ++row) {
		for (int col = 0; col < get_width(); ++col) {
			if (get_cell_domain(row, col).size() == 1) {
				b.set_cell_value(row, col, *get_cell_domain(row, col).begin());
			}
		}
	}

	return b;
}

std::vector<std::vector<std::set<int>>> DomainBoard::get_board() const
{
	return _board;
}

void DomainBoard::set_board(const std::vector<std::vector<std::set<int>>>& board)
{
	for (int row = 0; row < get_width(); ++row) {
		for (int col = 0; col < get_width(); ++col) {
			_board[row][col] = board[row][col];
		}
	}
}

void DomainBoard::print_board() const
{
	for (int row = 0; row < get_width(); ++row) {
		if (row % 3 == 0) {
			printThickSeparator();
		}
		else {
			printThinSeparator();
		}
		for (int i = 1; i <= 3; i++) {
			for (int col = 0; col < get_width(); ++col) {
				printCell(_board[row][col], i);
				if (col % 3 == 2 && col != 8) {
					std::cout << "|";
				}
			}
			std::cout << "\n";
		}
	}
	printThickSeparator();
}

void DomainBoard::printCell(const std::set<int>& domain, int row) const
{
	for (int i = row*3-2; i <= row*3; ++i) {
		if (domain.find(i) != domain.end()) {
			std::cout << i;
		}
		else {
			std::cout << ".";
		}

		/*if (i % 3 != 0) {
			std::cout << ",";
		}
		else if (i != 9) {
			std::cout << "|";
		}*/
	}

	std::cout << "|";
}

void DomainBoard::printThinSeparator() const
{
	for (int i = 0; i < 3; ++i) {
		std::cout << "---|---|---||";
	}
	std::cout << "\n";
}

void DomainBoard::printThickSeparator() const
{
	for (int i = 0; i < 3; ++i) {
		std::cout << "===|===|===||";
	}
	std::cout << "\n";
}

std::set<int> DomainBoard::get_cell_domain(const Cell& cell) const
{
	return get_cell_domain(cell.get_location().x, cell.get_location().y);
}

std::set<int> DomainBoard::get_cell_domain(int row, int col) const
{
	return get_board()[row][col];
}

void DomainBoard::set_cell_domain(const std::set<int>& domain, const Cell& cell)
{
	set_cell_domain(domain, cell.get_location().x, cell.get_location().y);
}

void DomainBoard::set_cell_domain(const std::set<int>& domain, int row, int col)
{
	_board[row][col].clear();
	_board[row][col].insert(domain.begin(), domain.end());
}

bool DomainBoard::is_solved() const
{
	for (int row = 0; row < get_width(); ++row) {
		for (int col = 0; col < get_width(); ++col) {
			if (get_cell_domain(row, col).size() > 1 || !is_valid_move(row, col, *get_cell_domain(row, col).begin())) {
				return false;
			}
		}
	}

	return true;
}

bool DomainBoard::is_valid_move(const Cell& cell, int value) const
{
	return is_valid_move(cell.get_location().x, cell.get_location().y, value);
}

bool DomainBoard::is_valid_move(int row, int col, int value) const
{
	// rows
	for (int i = 0; i < get_width(); ++i) {
		if (i == col) {
			continue;
		}

		// only compare against a cell if their domains are solved
		if (get_cell_domain(row, i).size() == 1 && *get_cell_domain(row, i).begin() == value) {
			return false;
		}		
	}

	// columns
	for (int i = 0; i < get_width(); ++i) {
		if (i == row) {
			continue;
		}

		// only compare against a cell if their domains are solved
		if (get_cell_domain(i, col).size() == 1 && *get_cell_domain(i, col).begin() == value) {
			return false;
		}
	}

	// squares
	int row_init = (row / 3) * 3;
	int col_init = (col / 3) * 3;

	for (int i = row_init; i < row_init + 3; i++) {
		for (int j = col_init; j < col_init + 3; j++) {
			if (i == row && j == col) {
				continue;
			}

			// only compare against a cell if their domains are solved
			if (get_cell_domain(i, j).size() == 1 && *get_cell_domain(i, j).begin() == value) {
				return false;
			}
		}
	}

	return true;
}

int DomainBoard::get_width() const
{
	return 9;
}

void DomainBoard::initialize_board()
{
    for (int i = 0; i < get_width(); i++) {
        std::vector<std::set<int>> row;
        for (int j = 0; j < get_width(); j++) {
            row.push_back(_valid_values);
        }

        _board.push_back(row);
    }
}