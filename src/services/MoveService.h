#ifndef __MOVESERVICE_H_
#define __MOVESERVICE_H_

#include "../chess-board/Board.h"
#include "../chess-board/ChessColour.h"
#include "../chess-board/Turn.h"
#include <vector>

namespace chesspp {
class MoveService {
private:
  ChessColour &to_play;
  Board &board;
  void step(std::pair<char, int> &, std::vector<chesspp::Turn> &);
  void double_step(std::pair<char, int> &, std::vector<chesspp::Turn> &);
  void lanes(std::pair<char, int> &, std::vector<chesspp::Turn> &);
  void diags(std::pair<char, int> &, std::vector<chesspp::Turn> &);
  void kings_walk(std::pair<char, int> &, std::vector<chesspp::Turn> &);
  void jump(std::pair<char, int> &, std::vector<chesspp::Turn> &);

public:
  MoveService(ChessColour &, Board &);
  const std::vector<Turn> GetAvailableTurns(void);
};
} // namespace chesspp

#endif // __MOVESERVICE_H_
