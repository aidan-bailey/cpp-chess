#include "chess-board/board.h"
#include "chess_colour.h"
#include "linear_search.hpp"
#include "services/game_service.h"
#include "services/game_state.h"
#include "square_location.h"
#include "turn.h"
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

int main(int argc, char *argv[]) {
  chesspp::GameService game_service;
  while (true) {
    std::string buffer;
    std::string colour =
        game_service.GetToPlay() == chesspp::White ? "White" : "Black";
    if (game_service.GetState() == chesspp::Playing) {
      auto piece_location = game_service.GetMoveablePieces();
      buffer = "Available pieces: \n";
      for (int i = 0; i < piece_location.size(); i++) {
        buffer = buffer + piece_location[i].Col +
                 std::to_string(piece_location[i].Row) + '|';
      }
      buffer = buffer + "\nSelect source square ('xx' to concede): ";
      std::system("clear");
      std::cout << "ChessPlusPlus " << std::endl;
      game_service.PrintBoard();
      std::cout << buffer;
      std::string selected_source;
      std::getline(std::cin, selected_source);
      if (selected_source == "")
        continue;
      if (selected_source.length() != 2)
        continue;
      if (selected_source == "xx") {
        game_service.Concede();
        continue;
      }
      char src_col = selected_source[0];
      int src_row = selected_source[1] - 48;
      if (src_col < 'a' || src_col > 'h' || src_row < 1 || src_row > 8)
        continue;
      chesspp::SquareLocation source{src_col, src_row};
      auto possible_moves = game_service.GetPossibleMoves(source);
      if (possible_moves.size() == 0)
        continue;

      buffer = buffer + src_col + std::to_string(src_row) + '\n';
      for (int i = 0; i < possible_moves.size(); i++) {
        buffer = buffer + possible_moves[i].Col +
                 std::to_string(possible_moves[i].Row) + '|';
      }
      buffer = buffer + "\nSelect target square ('bb' to go back): ";
      while (true) {
        std::system("clear");
        std::cout << "ChessPlusPlus " << std::endl;
        game_service.PrintBoard();
        std::cout << buffer;
        std::string selected_target;
        std::getline(std::cin, selected_target);
        if (selected_target == "")
          continue;
        if (selected_target.length() != 2)
          continue;
        if (selected_target == "bb") {
          break;
        }
        char trg_col = selected_target[0];
        int trg_row = selected_target[1] - 48;
        if (trg_col < 'a' || trg_col > 'h' || trg_row < 1 || trg_row > 8)
          continue;
        chesspp::SquareLocation target{trg_col, trg_row};
        if (search::linear_search(target, &possible_moves[0],
                                  possible_moves.size()) == -1)
          continue;
        chesspp::Turn chosen_move{source, target};
        game_service.PlayTurn(chosen_move);
        break;
      }
    } else {

      char instruction;
      std::system("clear");
      std::cout << "ChessPlusPlus " << std::endl;
      game_service.PrintBoard();
      std::cout << "[e]xit [r]eset" << std::endl;
      std::cin >> instruction;
      switch (instruction) {
      case 'e':
        return 0;
      case 'r':
        game_service.ResetGame();
        continue;
      default:
        continue;
      }
    }
  }
  return 0;
}
