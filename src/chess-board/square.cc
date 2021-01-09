#include "square.h"
#include "square_location.h"

/**
 * Square constructor.
 **/
chesspp::Square::Square(void)
    : piecePtr(nullptr), occupied(false), location(SquareLocation('a', 1)) {}

/**
 * Square constructor.
 **/
chesspp::Square::Square(chesspp::SquareLocation l)
    : piecePtr(nullptr), occupied(false), location(l) {}

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
  return *piecePtr;
}

/**
 * Checks whether the square contains a piece.
 *
 * @return Bool whether or not the square is occupied.
 **/
const bool chesspp::Square::IsOccuppied(void) const { return occupied; }

/**
 * Acquires square location
 **/
chesspp::SquareLocation chesspp::Square::GetLocation(void) const {
  return location;
}

/**
 * Add a piece to the square.
 *
 * @param type Type of piece to add.
 * @param colour Colour of piece to add.
 **/
bool chesspp::Square::AddPiece(chesspp::PieceType type,
                               chesspp::ChessColour colour) {
  RemovePiece();
  piecePtr = new Piece{type, colour};
  occupied = true;
  return true;
}

/**
 * Remove a piece from the square.
 *
 * @return Whether or not a piece has been removed from the square.
 **/
void chesspp::Square::RemovePiece(void) {
  if (!occupied)
    return;
  delete piecePtr;
  occupied = false;
};

/**
 * Move operator.
 **/
chesspp::Square &chesspp::Square::operator=(Square &&s) {
  // check if source square is occupied
  if (!s.IsOccuppied())
    return *this;

  // check if target square is occupied
  if (IsOccuppied())
    RemovePiece();

  // move piece
  Piece *temp = &*s.piecePtr;
  s.piecePtr = nullptr;
  s.occupied = false;
  this->piecePtr = temp;
  this->occupied = true;

  return *this;
}

/**
 * Copy operator.
 **/
chesspp::Square &chesspp::Square::operator=(const Square &s) {
  this->location = s.location;
  if (!s.IsOccuppied()) {
    RemovePiece();
    return *this;
  }
  this->AddPiece(s.GetPiece().Type, s.GetPiece().Colour);
  return *this;
}
