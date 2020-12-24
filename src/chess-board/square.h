#ifndef __SQUARE_H_
#define __SQUARE_H_

#include "chess_colour.h"
#include "piece.h"
#include "piece_type.h"

namespace chesspp {
class Square {
private:
  Piece *piecePtr;
  bool occupied;

public:
  Square(void);
  ~Square(void);
  const Piece &GetPiece(void) const;
  const bool IsOccuppied(void) const;
  bool AddPiece(chesspp::PieceType, chesspp::ChessColour);
  void RemovePiece(void);

  Square &operator=(Square &&);
  Square &operator=(const Square &);
};
} // namespace chesspp

#endif // __SQUARE_H_
