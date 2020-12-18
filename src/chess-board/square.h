#ifndef __SQUARE_H_
#define __SQUARE_H_

#include "chess_colour.h"
#include "piece.h"
#include "piece_type.h"

namespace chesspp {
class Square {
private:
  Piece *PiecePtr;

public:
  Square(void);
  ~Square(void);
  bool IsOccuppied(void);
  bool AddPiece(chesspp::PieceType, chesspp::ChessColour);
  bool RemovePiece(void);
  const Piece &GetPiece(void);

  Square &operator=(Square &);
};
} // namespace chesspp

#endif // __SQUARE_H_
