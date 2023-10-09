#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <iostream>
#include "Generator.h"
#include "Board.h"
#include "DomainBoard.h"
#include "Solver.h"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

 std::vector<std::vector<std::shared_ptr<Cell>>> generate_sudoku(Difficulty difficulty) {
     Generator gen;
     Board board(gen.generate_board());
     gen.remove_values(board, difficulty);
     return board.get_board();
 }

 std::vector<std::vector<std::shared_ptr<Cell>>> generate_sudoku() {
     Generator gen;
     Board board(gen.generate_board());
     return board.get_board();
 }

 std::vector<std::vector<std::shared_ptr<Cell>>> solve_sudoku(Board& input_puzzle) {
     Solver solver(input_puzzle);

     return solver.solve().get_board();
 }

 Difficulty stringToDifficulty(const std::string& difficulty) {
     if (difficulty == "easy") {
         return EASY;
     }
     else if (difficulty == "medium") {
         return MEDIUM;
     }
     else if (difficulty == "hard") {
         return HARD;
     }
     else {
         return EXTREME;
     }
 }

 Board parse_puzzle(const web::json::array& input_array)
 {
     Board b;

     for (int i = 0; i < 9; i++) {
         json::value row = input_array.at(i);
         for (int j = 0; j < 9; j++) {
             b.set_cell_value(i, j, row.at(j).as_integer());
         }
     }
     return b;
 }

 void handle_get(http_request request) {
     if (request.relative_uri().path() == U("/sudoku/generate")) {
         std::cout << "Generate" << std::endl;
         // Extract the query parameters from the URI
         auto query_params = request.relative_uri().split_query(request.relative_uri().query());
         std::cout << query_params.size() << std::endl;
         std::vector<std::vector<std::shared_ptr<Cell>>> generated_puzzle;
         if (query_params.size() > 0) {
             std::cout << conversions::to_utf8string(query_params[U("difficulty")]) << std::endl;
             generated_puzzle = generate_sudoku(stringToDifficulty(conversions::to_utf8string(query_params[U("difficulty")])));
         }
         else {
             generated_puzzle = generate_sudoku();
         }

         // Convert the 2D vector into a JSON array of arrays
         json::value json_puzzle = json::value::array();
         for (size_t i = 0; i < generated_puzzle.size(); ++i) {
             json::value json_row = json::value::array();
             for (size_t j = 0; j < generated_puzzle[i].size(); ++j) {
                 json_row[j] = json::value::number(generated_puzzle[i][j]->get_value());
             }
             json_puzzle[i] = json_row;
         }

         http_response response(status_codes::OK);
         response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
         response.set_body(json_puzzle);
         request.reply(response);

     }
     else {
         request.reply(status_codes::NotFound);
     }
 }

 void handle_post(http_request request) {
     if (request.relative_uri().path() == U("/sudoku/solve")) {
         std::cout << "Solve" << std::endl;
         json::value body = request.extract_json().get();

         // Check if the "puzzle" key exists and is an array
         if (!body.has_field(U("puzzle")) || !body[U("puzzle")].is_array()) {
             std::cout << "Bad Request" << std::endl;
             request.reply(status_codes::BadRequest, U("Invalid data format! Expected 'puzzle' field with 2D array."));
             return;
         }

         json::array jsonArray = body[U("puzzle")].as_array();
         
         std::vector<std::vector<int>> cells;
         for (int i = 0; i < 9; ++i) {
             std::vector<int> row;
             for (int j = 0; j < 9; ++j) {
                 row.push_back(jsonArray[i][j].as_integer());
             }
             cells.push_back(row);
         }

         Board b(cells);
         auto solved_puzzle = solve_sudoku(b);

         // Convert the 2D vector into a JSON array of arrays
         json::value json_puzzle = json::value::array();
         for (size_t i = 0; i < solved_puzzle.size(); ++i) {
             json::value json_row = json::value::array();
             for (size_t j = 0; j < solved_puzzle[i].size(); ++j) {
                 json_row[j] = json::value::number(solved_puzzle[i][j]->get_value());
             }
             json_puzzle[i] = json_row;
         }

         http_response response(status_codes::OK);
         response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
         response.set_body(json_puzzle);
         request.reply(response);
     }
     else {
         request.reply(status_codes::NotFound);
     }
 }

 void handle_options(http_request request) {
     http_response response(status_codes::OK);
     response.headers().add(U("Allow"), U("GET, POST, OPTIONS"));
     response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
     response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
     response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
     request.reply(response);
 }


int main() {
     http_listener listener(U("http://localhost:8080"));

     listener.support(methods::GET, handle_get);
     listener.support(methods::POST, handle_post);
     listener.support(methods::OPTIONS, handle_options);

     try {
         listener.open()
             .then([&listener]() { std::cout << "Listener open" << std::endl; })
             .wait();

         std::string line;
         std::getline(std::cin, line);
     } catch (std::exception& e) {
         std::cout << "Error: " << e.what() << std::endl;
     }

    return 0;
}
