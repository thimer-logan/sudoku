#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <iostream>
#include "Generator.h"
#include "Board.h"

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

 utility::string_t solve_sudoku(utility::string_t input_puzzle) {
     return U("Solved Sudoku puzzle");
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
     else if (difficulty == "extreme") {
         return EXTREME;
     }
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
         request.extract_json()
             .then([](web::json::value json_data) {
                 auto input_puzzle = json_data[U("puzzle")].as_string();
                 auto solved_puzzle = solve_sudoku(input_puzzle);
                 return json::value::string(solved_puzzle);
             })
             .then([&](json::value json_response) {
                 request.reply(status_codes::OK, json_response);
             });
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
