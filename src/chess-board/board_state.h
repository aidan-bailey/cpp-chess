#ifndef __BOARD_STATE_H_
#define __BOARD_STATE_H_

#include "square.h"
namespace chesspp {
struct BoardState {
  Square squares[8][8];
  BoardState(void);
};
} // namespace chesspp

#endif // __BOARD_STATE_H_
