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
  void cleanBoard(void);
  Square &at(char, int);

public:
  Board(void);
  ~Board(void);
  const Square &At(char, int) const;
  void Reset(void);
  bool MakeMove(std::pair<char, int>, std::pair<char, int>);
  std::string toString(void) const;
  Board &operator=(const Board &);
};
} // namespace chesspp

#endif // __BOARD_H_
