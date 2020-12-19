#ifndef __MOVE_SERVICE_H_
#define __MOVE_SERVICE_H_

#include "../chess-board/board.h"
#include "../chess-board/chess_colour.h"
#include "../chess-board/turn.h"
#include <vector>

namespace chesspp {
class MoveService {
private:
  ChessColour &to_play;
  Board &board;
  bool isValid(char, int) const;
  void step(std::pair<char, int> &, std::vector<chesspp::Turn> &) const;
  void double_step(std::pair<char, int> &, std::vector<chesspp::Turn> &) const;
  void lanes(std::pair<char, int> &, std::vector<chesspp::Turn> &) const;
  void diags(std::pair<char, int> &, std::vector<chesspp::Turn> &) const;
  void kings_walk(std::pair<char, int> &, std::vector<chesspp::Turn> &) const;
  void jump(std::pair<char, int> &, std::vector<chesspp::Turn> &) const;

public:
  MoveService(ChessColour &, Board &);
  const std::vector<Turn> GetAvailableTurns(void);
};
} // namespace chesspp

#endif // __MOVESERVICE_H_
