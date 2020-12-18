#include "square.h"

bool chesspp::Square::IsOccuppied(void) { return PiecePtr != nullptr; }

bool chesspp::Square::AddPiece(chesspp::PieceType type,
                               chesspp::ChessColour colour) {
  if (IsOccuppied())
    return false;
  PiecePtr = new Piece{type, colour};
  return true;
}

bool chesspp::Square::RemovePiece(void) {
  if (!IsOccuppied())
    return false;
  delete PiecePtr;
  PiecePtr = nullptr;
  return true;
}

const chesspp::Piece &chesspp::Square::GetPiece(void) { return *PiecePtr; }

chesspp::Square::Square(void) : PiecePtr(nullptr) {}

chesspp::Square &chesspp::Square::operator=(Square &r) {
  if (!r.IsOccuppied())
    return *this;
  RemovePiece();
  Piece *temp = r.PiecePtr;
  r.PiecePtr = nullptr;
  this->PiecePtr = temp;
  return *this;
}
