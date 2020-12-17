#include "Board.h"
#include "ChessColour.h"
#include "PieceType.h"
#include <string>
#include <utility>

chesspp::Board::Board(void) {
  PieceType const minor_piece_types[8]{Rook, Knight, Bishop, Queen,
                                       King, Bishop, Knight, Rook};
  for (int j = 0; j < 8; j++) {
    // white minor
    state[j][0].AddPiece(minor_piece_types[j], White);
    // white pawn
    state[j][1].AddPiece(Pawn, White);
    // black pawn
    state[j][6].AddPiece(Pawn, Black);
    // black minor
    state[j][7].AddPiece(minor_piece_types[j], Black);
  }
}

chesspp::Board::~Board(void) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      state[j][i].RemovePiece();
    }
  }
}

chesspp::Square &chesspp::Board::At(char col, int row) {
  int j(int(col - 97)), i(row - 1);
  return state[j][i];
}

bool chesspp::Board::MakeMove(std::pair<char, int> from,
                              std::pair<char, int> to) {
  Square &from_sqr = At(from.first, from.second);
  if (!from_sqr.IsOccuppied())
    return false;
  Square &to_sqr = At(to.first, to.second);
  to_sqr = from_sqr;
  return true;
}

std::string chesspp::Board::toString(void) {
  std::string result;
  result = result + "---------------------------\n";
  for (int i = 7; i > -1; i--) {
    result = result + ' ' + std::to_string(i + 1) + '|';
    for (int j = 0; j < 8; j++) {
      if (state[j][i].IsOccuppied())
        result = result +
                 chesspp::ChessColourNames[state[j][i].GetPiece().Colour] +
                 chesspp::PieceTypeNames[state[j][i].GetPiece().Type] + '|';
      else {
        result = result + "XX" + '|';
      }
    }
    if (i != 0)
      result += '\n';
  }
  result = result + "\n  | a| b| c| d| e| f| g| h|";
  result = result + "\n---------------------------";
  return result;
}
