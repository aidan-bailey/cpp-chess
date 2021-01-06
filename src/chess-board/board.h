#ifndef __BOARD_H_
#define __BOARD_H_

#include "board_state.h"
#include "piece.h"
#include "square.h"
#include "square_location.h"
#include "turn.h"
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace chesspp {
class Board {
private:
  BoardState state;
  void populateDefaultBoard(void);
  void cleanBoard(void);
  Square &at(char, int);

public:
  Board(void);
  Board(const Board &);
  ~Board(void);
  const Square &At(SquareLocation) const;
  void Reset(void);
  Board &MakeMove(SquareLocation, SquareLocation);
  std::string toString(void) const;
  Board &operator=(const Board &);
};
} // namespace chesspp

#endif // __BOARD_H_
