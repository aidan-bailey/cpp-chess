#ifndef __PIECETYPE_H_
#define __PIECETYPE_H_

namespace chesspp {

enum PieceType {
  King,
  Queen,
  Bishop,
  Knight,
  Rook,
  Pawn,
};

static const char *PieceTypeNames[] = {"K", "Q", "B", "N", "R", "P"};

} // namespace chesspp

#endif // __SQUARETYPE_H_
