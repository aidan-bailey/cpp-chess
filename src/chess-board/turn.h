#ifndef __MOVE_H_
#define __MOVE_H_

#include "square_location.h"
#include <cstdint>
#include <utility>

namespace chesspp {
struct Turn {
  SquareLocation From;
  SquareLocation To;
  friend bool operator==(Turn &, Turn &);
};
bool operator==(chesspp::Turn &, chesspp::Turn &);
} // namespace chesspp

#endif // __MOVE_H_
