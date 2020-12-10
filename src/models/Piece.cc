#include "Piece.h"

models::Piece::Piece(enums::ChessPieceType type, enums::ChessColour colour,
                     int value, int id) {
  Type = type;
  Colour = colour;
  Value = value;
  Id = id;
}
