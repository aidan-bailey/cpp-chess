#ifndef __PIECE_H_
#define __PIECE_H_

#include "ChessColour.h"
#include "ChessPieceType.h"

namespace models {

struct Piece {
  enums::ChessPieceType Type;
  enums::ChessColour Colour;
  Piece(enums::ChessPieceType type, enums::ChessColour colour);
};

} // namespace models

#endif // __PIECE_H_
