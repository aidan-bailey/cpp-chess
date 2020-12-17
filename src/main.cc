#include "ChessColour.h"
#include "Turn.h"
#include "chess-board/Board.h"
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
    std::cout << "-------------------------" << std::endl;
    game_service.PrintBoard();
    std::cout << "-------------------------" << std::endl;
    if (game_service.GetState() == chesspp::Ready) {
      auto piece_location = game_service.GetMoveablePieces();

      std::string colour =
          game_service.GetToPlay() == chesspp::White ? "White" : "Black";
      std::cout << colour << " to play." << std::endl;
      std::cout << "Available pieces: " << std::endl;
      std::cout << "0.Concede|";
      for (int i = 0; i < piece_location.size(); i++) {
        std::cout << i + 1 << '.' << piece_location[i].first
                  << piece_location[i].second << '|';
      }
      std::cout << std::endl << "Select piece to move: ";
      int selected_source;
      std::cin >> selected_source;
      if (selected_source == 0) {
        game_service.Concede();
        continue;
      }

      if ((selected_source < 1 || selected_source > piece_location.size()))
        continue;

      std::pair<char, int> source = piece_location[selected_source - 1];
      auto possible_moves = game_service.GetPossibleMoves(source);
      std::cout << 0 << ".Return|";
      for (int i = 0; i < possible_moves.size(); i++) {
        std::cout << i + 1 << '.' << possible_moves[i].first
                  << possible_moves[i].second << '|';
      }
      std::cout << std::endl << "Select a square to move to: ";
      int selected_target(-1);
      while (selected_target < 0 || selected_target > possible_moves.size()) {
        std::cin >> selected_target;
      }
      if (selected_target == 0)
        continue;
      std::pair<char, int> target = possible_moves[selected_target - 1];

      chesspp::Turn chosen_move{source, target};
      game_service.PlayTurn(chosen_move);
    } else {
      std::string colour =
          game_service.GetToPlay() == chesspp::White ? "Black" : "White";
      std::cout << "Game over!" << std::endl
                << colour << " is victorious!" << std::endl;

      int instruction(-1);
      std::cout << "0. Exit|1. Reset" << std::endl;
      while (instruction != 0) {
        std::cin >> instruction;
        switch (instruction) {
        case 0:
          return 0;
          break;
        }
      }
    }
  }
  return 0;
}
