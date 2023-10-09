#pragma once

#include <utility>
#include <set>
#include <vector>
#include <memory>
#include "Board.h"
#include "DomainBoard.h"

class Solver {
public:
	Solver(Board& board);

	Board solve();

private:
	DomainBoard _board;

	Cell mrv_heuristic(DomainBoard& board);

	std::pair<std::vector<std::pair<int, int>>, bool> remove_domain_row(DomainBoard& board, int row, int col);

	std::pair<std::vector<std::pair<int, int>>, bool> remove_domain_column(DomainBoard& board, int row, int col);

	std::pair<std::vector<std::pair<int, int>>, bool> remove_domain_square(DomainBoard& board, int row, int col);
	
	void preprocess_consistency(DomainBoard& board);

	bool consistency(DomainBoard& board, std::set<std::pair<int, int>>& cells_to_process);

	std::pair<DomainBoard, bool> search(DomainBoard& board);
};
