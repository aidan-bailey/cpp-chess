#include "square.h"

/**
 * Square constructor.
 **/
chesspp::Square::Square(void) : PiecePtr(nullptr) {}

/**
 * Square destructor.
 **/
chesspp::Square::~Square(void) { RemovePiece(); }

/**
 * Acquires contained piece (if it exists).
 *
 * @return Reference to piece.
 **/
const chesspp::Piece &chesspp::Square::GetPiece(void) const {
  return *PiecePtr;
}

/**
 * Checks whether the square contains a piece.
 *
 * @return Bool whether or not the square is occupied.
 **/
const bool chesspp::Square::IsOccuppied(void) const {
  return PiecePtr != nullptr;
}

/**
 * Add a piece to the square.
 *
 * @param type Type of piece to add.
 * @param colour Colour of piece to add.
 * @return Bool whether or not the piece was successfully added.
 **/
bool chesspp::Square::AddPiece(chesspp::PieceType type,
                               chesspp::ChessColour colour) {
  if (IsOccuppied())
    return false;
  PiecePtr = new Piece{type, colour};
  return true;
}

/**
 * Remove a piece from the square.
 *
 * @return Whether or not a piece has been removed from the square.
 **/
bool chesspp::Square::RemovePiece(void) {
  if (!IsOccuppied())
    return false;
  delete PiecePtr;
  PiecePtr = nullptr;
  return true;
}

/**
 * Move operator allowing you to perform a 'move' from one square to another.
 **/
chesspp::Square &chesspp::Square::operator=(Square &&s) {
  if (!s.IsOccuppied())
    return *this;
  RemovePiece();
  Piece *temp = s.PiecePtr;
  s.PiecePtr = nullptr;
  this->PiecePtr = temp;
  return *this;
}

/**
 * Copy operator.
 **/
chesspp::Square &chesspp::Square::operator=(const Square &s) {
  if (!s.IsOccuppied())
    return *this;
  RemovePiece();
  this->AddPiece(s.GetPiece().Type, s.GetPiece().Colour);
  return *this;
}
