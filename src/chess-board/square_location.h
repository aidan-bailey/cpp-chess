#ifndef __SQUARE_LOCATION_H_
#define __SQUARE_LOCATION_H_

namespace chesspp {
struct SquareLocation {
  char Col;
  int Row;
  SquareLocation(char col, int row);
  friend bool operator==(SquareLocation &, SquareLocation &);
  SquareLocation(const SquareLocation &);
};
bool operator==(SquareLocation &, SquareLocation &);
} // namespace chesspp

#endif // __SQUARE_LOCATION_H_
