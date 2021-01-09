#ifndef __PIECE_H_
#define __PIECE_H_

#include "chess_colour.h"
#include "piece_type.h"
#include <utility>

namespace chesspp {
struct Piece {
  PieceType const Type;
  ChessColour const Colour;
  Piece(PieceType type, ChessColour colour);
  Piece &operator=(const Piece &);
};
} // namespace chesspp

#endif // __PIECE_H_
