#ifndef __BOARD_H_
#define __BOARD_H_

#include "piece.h"
#include "square.h"
#include "turn.h"
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace chesspp {
class Board {
private:
  Square state[8][8];
  void populateDefaultBoard(void);

public:
  Board(void);
  ~Board(void);
  void Reset(void);
  Square &At(char, int);
  bool MakeMove(std::pair<char, int>, std::pair<char, int>);
  std::string toString(void);
};
} // namespace chesspp

#endif // __BOARD_H_
