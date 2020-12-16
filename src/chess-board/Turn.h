#ifndef __MOVE_H_
#define __MOVE_H_

#include <cstdint>
#include <utility>

namespace chesspp {
struct Turn {
  std::pair<char, int> const From;
  std::pair<char, int> const To;
};
} // namespace chesspp

#endif // __MOVE_H_
