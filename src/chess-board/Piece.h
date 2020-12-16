#ifndef __PIECE_H_
#define __PIECE_H_

#include "ChessColour.h"
#include "PieceType.h"
#include <utility>

namespace chesspp {
struct Piece {
  PieceType const Type;
  ChessColour const Colour;
  Piece(PieceType type, ChessColour colour) : Type(type), Colour(colour){};
};
} // namespace chesspp

#endif // __PIECE_H_
