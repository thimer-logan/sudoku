#include "SudokuResourceFactory.h"

SudokuResourceFactory::SudokuResourceFactory() {
    _resource = std::make_shared<restbed::Resource>();
    _resource->set_path(
        "/sudoku/board"
    );

    _resource->set_method_handler("GET", [&](const std::shared_ptr<restbed::Session> session) {
        get_handler(session);
    });
}

std::shared_ptr<restbed::Resource> SudokuResourceFactory::get_resource() const {
    return _resource;
}

void SudokuResourceFactory::get_handler(const std::shared_ptr<restbed::Session> session) {
    std::vector<std::vector<int>> puzzle;
    puzzle.push_back({0, 1, 0, 0, 2, 3, 6, 0, 7});
    puzzle.push_back({0, 0, 0, 0, 0, 0, 9, 0, 0});
    puzzle.push_back({6, 0, 0, 0, 0, 0, 2, 5, 0});
    puzzle.push_back({0, 0, 4, 1, 0, 2, 5, 3, 8});
    puzzle.push_back({0, 0, 2, 8, 0, 0, 4, 0, 0});
    puzzle.push_back({5, 0, 8, 0, 0, 0, 0, 6, 0});
    puzzle.push_back({8, 0, 0, 2, 0, 9, 0, 0, 0});
    puzzle.push_back({0, 0, 9, 0, 0, 0, 0, 0, 6});
    puzzle.push_back({0, 0, 0, 7, 3, 0, 0, 0, 0});

    nlohmann::json data(puzzle);
    auto content = data.dump();

    session->close(restbed::OK, content, {{"Content-Length", std::to_string(content.size())}});
}