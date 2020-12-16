#ifndef __SQUARE_H_
#define __SQUARE_H_

#include "ChessColour.h"
#include "Piece.h"
#include "PieceType.h"

namespace chesspp {
class Square {
private:
  Piece *PiecePtr;

public:
  Square(void);
  bool IsOccuppied(void);
  bool AddPiece(chesspp::PieceType, chesspp::ChessColour);
  bool RemovePiece(void);
  const Piece &GetPiece(void);

  Square &operator=(Square &);
};
} // namespace chesspp

#endif // __SQUARE_H_
