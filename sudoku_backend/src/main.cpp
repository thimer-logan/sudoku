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

// Replace with your Sudoku generator and solver functions
 std::vector<std::vector<std::shared_ptr<Cell>>> generate_sudoku() {
     Generator gen;
     Board board(gen.generate_board());
     return board.get_board();
 }

 utility::string_t solve_sudoku(utility::string_t input_puzzle) {
     return U("Solved Sudoku puzzle");
 }

 void handle_get(http_request request) {
     if (request.relative_uri().path() == U("/sudoku/generate")) {
         auto generated_puzzle = generate_sudoku();

         // Convert the 2D vector into a JSON array of arrays
         json::value json_puzzle = json::value::array();
         for (size_t i = 0; i < generated_puzzle.size(); ++i) {
             json::value json_row = json::value::array();
             for (size_t j = 0; j < generated_puzzle[i].size(); ++j) {
                 json_row[j] = json::value::number(generated_puzzle[i][j]->get_value());
             }
             json_puzzle[i] = json_row;
         }

         request.reply(status_codes::OK, json_puzzle);
     } else {
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
     } else {
         request.reply(status_codes::NotFound);
     }
 }


int main() {
     http_listener listener(U("http://localhost:8080"));

     listener.support(methods::GET, handle_get);
     listener.support(methods::POST, handle_post);

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
