#include "turn.h"

bool chesspp::operator==(Turn &t1, Turn &t2) {
  return (t1.From == t2.From && t1.To == t2.To);
}
