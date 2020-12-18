#ifndef __MOVE_H_
#define __MOVE_H_

#include <cstdint>
#include <utility>

namespace chesspp {
struct Turn {
  std::pair<char, int> From;
  std::pair<char, int> To;
  friend bool operator==(Turn&, Turn&);
};
bool operator==(chesspp::Turn&, chesspp::Turn&);
} // namespace chesspp

#endif // __MOVE_H_
