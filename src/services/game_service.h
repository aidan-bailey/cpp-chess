#ifndef __GAME_SERVICE_H_
#define __GAME_SERVICE_H_

#include "../chess-board/board.h"
#include "../chess-board/chess_colour.h"
#include "game_state.h"
#include "move_utility.h"
#include "square_location.h"
#include <utility>
#include <vector>

namespace chesspp {
class GameService {
private:
  // move service
  MoveUtility move_util;
  // board object
  Board board;
  // current turn colour variable
  ChessColour to_play;
  // current turn number
  int turn_counter;
  // current game history
  std::vector<Turn> turn_list;
  // current turn possible move list
  std::vector<Turn> possible_move_list;
  // current game state
  GameState state;
  // flips colour to next player
  void flipColour(void);

public:
  // game service default constructor
  GameService(void);
  // getter for current turn colour
  const ChessColour &GetToPlay(void);
  // getter for current game state
  const GameState &GetState(void);
  // gets current possible turn list
  const std::vector<Turn> &GetPossibleTurns(void);
  // gets current moveable pieces
  const std::vector<SquareLocation> GetMoveablePieces(void);
  // gets possible moves for a specific piece
  const std::vector<SquareLocation> GetPossibleMoves(SquareLocation);
  // attempt to play a turn
  bool PlayTurn(Turn);
  // concedes the game for the current player
  void Concede(void);
  // resets the game
  void ResetGame(void);
  // prints the board and current state
  void PrintBoard(void);
};
} // namespace chesspp

#endif // __GAME_SERVICE_H_
