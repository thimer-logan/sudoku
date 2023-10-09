#include "Solver.h"

Solver::Solver(Board& board) : _board(board.get_board())
{
	_board.print_board();
	std::cout << "\n\n" << std::endl;
}

Board Solver::solve()
{
	preprocess_consistency(_board);
	return search(_board).first.to_board();
}

Cell Solver::mrv_heuristic(DomainBoard& board)
{
	const int WIDTH = board.get_width();
	int minimum_val = 10000;
	int minimum_row = 0;
	int minimum_col = 0;

	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < WIDTH; j++) {
			size_t domain_size = board.get_cell_domain(i, j).size();
			if (domain_size > 1 && domain_size < minimum_val) {
				minimum_val = domain_size;
				minimum_row = i;
				minimum_col = j;
			}
		}
	}

	return Cell(minimum_row, minimum_col);
}

std::pair<std::vector<std::pair<int, int>>, bool> Solver::remove_domain_row(DomainBoard& board, int row, int col)
{
	std::vector<std::pair<int, int>> variables_assigned;
	const auto current_domain_value = *board.get_cell_domain(row, col).begin();

	for (int j = 0; j < board.get_width(); ++j) {
		if (j != col) {
			std::set<int> new_domain = board.get_cell_domain(row, j);

			new_domain.erase(current_domain_value);

			if (new_domain.size() == 0) {
				return { {}, true };
			}

			if (new_domain.size() == 1 && board.get_cell_domain(row, j).size() > 1) {
				variables_assigned.emplace_back(row, j);
			}

			board.set_cell_domain(new_domain, row, j);
		}
	}

	return { variables_assigned, false };
}

std::pair<std::vector<std::pair<int, int>>, bool> Solver::remove_domain_column(DomainBoard& board, int row, int col)
{
	std::vector<std::pair<int, int>> variables_assigned;
	const auto current_domain_value = *board.get_cell_domain(row, col).begin();

	for (int j = 0; j < board.get_width(); ++j) {
		if (j != row) {
			std::set<int> new_domain = board.get_cell_domain(j, col);

			new_domain.erase(current_domain_value);

			if (new_domain.size() == 0) {
				return { {}, true };
			}

			if (new_domain.size() == 1 && board.get_cell_domain(j, col).size() > 1) {
				variables_assigned.emplace_back(j, col);
			}

			board.set_cell_domain(new_domain, j, col);
		}
	}

	return { variables_assigned, false };
}

std::pair<std::vector<std::pair<int, int>>, bool> Solver::remove_domain_square(DomainBoard& board, int row, int col)
{
	std::vector<std::pair<int, int>> variables_assigned;
	const int row_init = (row / 3) * 3;
	const int col_init = (col / 3) * 3;
	const auto current_domain_value = *board.get_cell_domain(row, col).begin();

	for (int i = row_init; i < row_init + 3; i++) {
		for (int j = col_init; j < col_init + 3; j++) {
			if (i == row && j == col) {
				continue;
			}

			std::set<int> new_domain = board.get_cell_domain(i, j);

			new_domain.erase(current_domain_value);

			if (new_domain.size() == 0) {
				return { {}, true };
			}

			if (new_domain.size() == 1 && board.get_cell_domain(i, j).size() > 1) {
				variables_assigned.emplace_back(i, j);
			}

			board.set_cell_domain(new_domain, i, j);
		}
	}

	return { variables_assigned, false };
}

void Solver::preprocess_consistency(DomainBoard& board)
{
	std::set<std::pair<int, int>> q;
	for (int i = 0; i < board.get_width(); i++) {
		for (int j = 0; j < board.get_width(); j++) {
			if (board.get_cell_domain(i, j).size() == 1) {
				q.emplace(i, j);
			}
		}
	}

	consistency(board, q);
}

bool Solver::consistency(DomainBoard& board, std::set<std::pair<int, int>>& cells_to_process)
{
	while (!cells_to_process.empty()) {
		int row = cells_to_process.begin()->first;
		int col = cells_to_process.begin()->second;
		cells_to_process.erase(*cells_to_process.begin());

		auto rows = remove_domain_row(board, row, col);
		auto columns = remove_domain_column(board, row, col);
		auto squares = remove_domain_square(board, row, col);

		if (rows.second || columns.second || squares.second) {
			return true;
		}

		cells_to_process.insert(rows.first.begin(), rows.first.end());
		cells_to_process.insert(columns.first.begin(), columns.first.end());
		cells_to_process.insert(squares.first.begin(), squares.first.end());
	}

	return false;
}

std::pair<DomainBoard, bool> Solver::search(DomainBoard& board)
{
	if (board.is_solved()) {
		return { board, false };
	}

	Cell next_best = mrv_heuristic(board);

	for (int domain : board.get_cell_domain(next_best)) {
		if (board.is_valid_move(next_best, domain)) {
			DomainBoard test_board(board);
			test_board.set_cell_domain({ domain }, next_best);

			std::set<std::pair<int, int>> cell;
			cell.emplace(next_best.get_location().x, next_best.get_location().y);
			if (!consistency(test_board, cell)) {
				auto result = search(test_board);
				if (!result.second) {
					return result;
				}
			}
		}
	}

	return { board, true };
}