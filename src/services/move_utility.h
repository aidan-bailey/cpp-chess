#ifndef __MOVE_SERVICE_H_
#define __MOVE_SERVICE_H_

#include "../chess-board/board.h"
#include "../chess-board/chess_colour.h"
#include "../chess-board/square_location.h"
#include "../chess-board/turn.h"
#include <vector>

namespace chesspp {
class MoveUtility {
private:
  static bool isValid(char, int);
  static std::vector<chesspp::Turn> step(const Board &, ChessColour,
                                         SquareLocation);
  static std::vector<chesspp::Turn> double_step(const Board &, ChessColour,
                                                SquareLocation);
  static std::vector<chesspp::Turn> lanes(const Board &, ChessColour,
                                          SquareLocation);
  static std::vector<chesspp::Turn> diags(const Board &, ChessColour,
                                          SquareLocation);
  static std::vector<chesspp::Turn> kings_walk(const Board &, ChessColour,
                                               SquareLocation);
  static std::vector<chesspp::Turn> jump(const Board &, ChessColour,
                                         SquareLocation);
  static std::vector<Turn> getAllAvailableTurns(const Board &, ChessColour,
                                                const std::vector<Turn> &);
  static void removeIllegals(const Board &, ChessColour, std::vector<Turn> &,
                             std::vector<Turn>);

public:
  static std::vector<Turn> GetAvailableTurns(const Board &, ChessColour,
                                             const std::vector<Turn>);
};
} // namespace chesspp

#endif
