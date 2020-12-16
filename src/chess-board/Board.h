#ifndef __BOARD_H_
#define __BOARD_H_

#include "Piece.h"
#include "Square.h"
#include "Turn.h"
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace chesspp {
class Board {
private:
  Square state[8][8];

public:
  Board(void);
  ~Board(void);
  const Square &At(char, int);
  bool MakeMove(Turn);
  std::string toString(void);
};
} // namespace chesspp

#endif // __BOARD_H_
