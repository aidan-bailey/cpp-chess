#include "piece.h"

chesspp::Piece::Piece(PieceType type, ChessColour colour)
    : Type(type), Colour(colour){};

/**
 * Copy constructor
 * */
chesspp::Piece &chesspp::Piece::operator=(const chesspp::Piece &&p) {
  return *new Piece(p.Type, p.Colour);
}
