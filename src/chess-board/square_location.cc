#include "square_location.h"

bool chesspp::operator==(SquareLocation &s1, SquareLocation &s2) {
  if (s1.col != s2.col)
    return false;
  if (s1.row != s2.row)
    return false;
  return true;
}
