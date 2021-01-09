#include "square_location.h"

chesspp::SquareLocation::SquareLocation(char col, int row)
    : Col(col), Row(row) {}

bool chesspp::operator==(SquareLocation &s1, SquareLocation &s2) {
  if (s1.Col != s2.Col)
    return false;
  if (s1.Row != s2.Row)
    return false;
  return true;
}

chesspp::SquareLocation::SquareLocation(const SquareLocation &sl) {
  this->Col = sl.Col;
  this->Row = sl.Row;
}
