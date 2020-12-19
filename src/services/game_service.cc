#include "game_service.h"
#include "board.h"
#include "chess_colour.h"
#include "game_state.h"
#include "linear_search.hpp"
#include "move_service.h"
#include "piece_type.h"
#include "turn.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/**
 * Flips colour to next player.
 **/
void chesspp::GameService::flipColour(void) {
  to_play = to_play == Black ? White : Black;
}

/**
 * Game service constructor.
 **/
chesspp::GameService::GameService(void)
    : to_play(chesspp::White), turn_counter(1), move_service(to_play, board),
      possible_move_list(move_service.GetAvailableTurns()), state(Playing){};

/**
 * Getter for current turn colour.
 *
 * @return ChessColour of this turn's player.
 **/
const chesspp::ChessColour &chesspp::GameService::GetToPlay(void) {
  return to_play;
}

/**
 * Getter for current game state.
 *
 * @return Current GameState.
 **/
const chesspp::GameState &chesspp::GameService::GetState(void) { return state; }

/**
 * Gets current possible turn list.
 *
 * @return Vector of possible turns.
 **/
const std::vector<chesspp::Turn> &chesspp::GameService::GetPossibleTurns(void) {
  return possible_move_list;
};

/**
 * Gets current moveable pieces.
 *
 * @return Vector of moveable pair locations.
 **/
const std::vector<std::pair<char, int>>
chesspp::GameService::GetMoveablePieces(void) {
  std::vector<std::pair<char, int>> result{
      {possible_move_list[0].From.first, possible_move_list[0].From.second}};
  for (auto source = possible_move_list.begin() + 1;
       source < possible_move_list.end(); source++) {
    if (result.back() == source->From)
      continue;
    result.emplace_back(source->From);
  }
  return result;
}

/**
 * Gets possible moves for a specific piece.
 *
 * @param location Location of piece to process.
 * @return Vector of possible target locations for the piece.
 **/
const std::vector<std::pair<char, int>>
chesspp::GameService::GetPossibleMoves(std::pair<char, int> location) {
  std::vector<std::pair<char, int>> result;
  for (auto iter = possible_move_list.begin(); iter < possible_move_list.end();
       iter++)
    if (iter->From == location)
      result.emplace_back(iter->To);
  return result;
}

/**
 * Attempts to play a turn.
 *
 * @param turn Turn to play.
 * @return Whether or not the turn was successfully played.
 **/
bool chesspp::GameService::PlayTurn(Turn turn) {
  if (search::linear_search(turn, &possible_move_list[0],
                            possible_move_list.size()) == -1)
    return false;
  board.MakeMove(turn.From, turn.To);
  turn_list.emplace_back(turn);
  flipColour();
  possible_move_list = move_service.GetAvailableTurns();
  for (auto ptr = possible_move_list.begin(); ptr < possible_move_list.end();
       ptr++) {
    const Square &square = board.At(ptr->To.first, ptr->To.second);
    if (square.IsOccuppied() && square.GetPiece().Type == King) {
      state = GameState(to_play);
      return false;
    }
  }
  turn_counter++;
  return true;
}

/**
 * Concedes the game for the current player.
 **/
void chesspp::GameService::Concede(void) {
  if (state != Playing)
    return;
  state = GameState(to_play == White ? Black : White);
}

/**
 * Resets the game.
 **/
void chesspp::GameService::ResetGame(void) {
  board.Reset();
  to_play = White;
  possible_move_list = move_service.GetAvailableTurns();
  turn_counter = 1;
  state = Playing;
}

/**
 * Prints the board and current state.
 **/
void chesspp::GameService::PrintBoard(void) {
  std::cout << board.toString() << std::endl;
  std::string colour = to_play == chesspp::White ? "White" : "Black";
  switch (state) {
  case Playing:
    std::cout << colour << " to play." << std::endl;
    break;
  default:
    std::cout << "Game over!" << std::endl
              << chesspp::GameStateNames[state] << '!' << std::endl;
  }
}
