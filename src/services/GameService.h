#ifndef __GAMESERVICE_H_
#define __GAMESERVICE_H_

#include "../chess-board/Board.h"
#include "../chess-board/ChessColour.h"
#include "GameState.h"
#include "MoveService.h"
#include <utility>
#include <vector>

namespace chesspp {
class GameService {
private:
  ChessColour to_play;
  int turn_counter;
  std::vector<Turn> turn_list;
  Board board;
  MoveService move_service;
  std::vector<Turn> possible_move_list;
  GameState state;
  void flipColour(void);

public:
  GameService(void);
  ChessColour GetToPlay(void);
  void PrintBoard(void);
  GameState GetState(void) const;
  std::vector<Turn> GetPossibleTurns(void);
  std::vector<std::pair<char, int>> GetMoveablePieces(void);
  std::vector<std::pair<char, int>> GetPossibleMoves(std::pair<char, int>);
  void Concede(void);
  bool PlayTurn(Turn);
};
} // namespace chesspp

#endif // __GAMESERVICE_H_
