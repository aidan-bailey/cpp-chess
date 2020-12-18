#include "ChessColour.h"
#include "Turn.h"
#include "chess-board/Board.h"
#include "linear_search.hpp"
#include "services/GameService.h"
#include "services/GameState.h"
#include <iostream>
#include <ostream>
#include <string>
#include <utility>

int main(int argc, char *argv[]) {
  chesspp::GameService game_service;
  while (true) {
    std::system("clear");
    std::cout << "ChessPlusPlus " << std::endl;
    game_service.PrintBoard();
    std::string colour =
        game_service.GetToPlay() == chesspp::White ? "White" : "Black";
    if (game_service.GetState() == chesspp::Playing) {
      auto piece_location = game_service.GetMoveablePieces();

      std::cout << colour << " to play." << std::endl;
      std::cout << "Available pieces: " << std::endl;
      for (int i = 0; i < piece_location.size(); i++) {
        std::cout << piece_location[i].first << piece_location[i].second << '|';
      }
      std::cout << std::endl << "Select source square ('xx' to concede): ";
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
      std::pair<char, int> source{src_col, src_row};
      auto possible_moves = game_service.GetPossibleMoves(source);
      if (possible_moves.size() == 0)
        continue;

      for (int i = 0; i < possible_moves.size(); i++) {
        std::cout << possible_moves[i].first << possible_moves[i].second << '|';
      }
      std::cout << std::endl << "Select target square ('bb' to go back): ";
      std::string selected_target;
      std::getline(std::cin, selected_target);
      if (selected_target == "")
        continue;
      if (selected_target.length() != 2)
        continue;
      if (selected_target == "bb") {
        continue;
      }
      char trg_col = selected_target[0];
      int trg_row = selected_target[1] - 48;
      if (trg_col < 'a' || trg_col > 'h' || trg_row < 1 || trg_row > 8)
        continue;
      std::pair<char, int> target{trg_col, trg_row};
      if (search::linear_search(target, &possible_moves[0],
                                possible_moves.size()) == -1)
        continue;
      chesspp::Turn chosen_move{source, target};
      game_service.PlayTurn(chosen_move);
    } else {

      std::cout << "Game over!" << std::endl
                << chesspp::GameStateNames[game_service.GetState()] << '!'
                << std::endl;

      char instruction;
      std::cout << "(e)xit" << std::endl;
      std::cin >> instruction;
      switch (instruction) {
      case 'e':
        break;
      default:
        break;
      }
      break;
    }
  }
  return 0;
}
