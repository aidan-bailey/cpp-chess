#include "Turn.h"

bool chesspp::operator==(Turn &t1, Turn &t2) {
  if (t1.From != t2.From)
    return false;
  if (t1.To != t2.To)
    return false;
  return true;
}
