#include "board.h"
#include "chess_colour.h"
#include "piece_type.h"
#include <string>
#include <utility>

/**
 * Board constructor.
 **/
chesspp::Board::Board(void) { populateDefaultBoard(); }

/**
 * Board destructor.
 **/
chesspp::Board::~Board(void) { cleanBoard(); }

/**
 * Takes in a column and row and returns (if it exists) the corresponding
 * square.
 *
 * @param col Column of requested square.
 * @param row Row of requested square.
 * @return Reference to square.
 **/
const chesspp::Square &chesspp::Board::At(char col, int row) const {
  int j(int(col - 97)), i(row - 1);
  return state[j][i];
}

/**
 * Resets the board to the default starting state.
 * */
void chesspp::Board::Reset(void) {
  this->~Board();
  populateDefaultBoard();
}

/**
 * Attempts to make a legal chess move.
 *
 * @param from Source square location pair.
 * @param to Target square location pair.
 * @return Bool specifying whether the move was successful.
 * */
bool chesspp::Board::MakeMove(std::pair<char, int> from,
                              std::pair<char, int> to) {
  Square &from_sqr = at(from.first, from.second);
  if (!from_sqr.IsOccuppied())
    return false;
  Square &to_sqr = at(to.first, to.second);
  to_sqr = std::move(from_sqr);
  return true;
}

/**
 * Board toString.
 * */
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

/**
 * Copy operator.
 **/
chesspp::Board &chesspp::Board::operator=(const Board &&b) {
  cleanBoard();
  for (char col = 'a'; col < 'h' + 1; col++) {
    for (int row = 1; row < 8 + 1; row++) {
      const Square &square = b.At(col, row);
      if (square.IsOccuppied()) {
        state[col][row] = square;
      }
    }
  }
  return *this;
}

/**
 * Default board populator.
 **/
void chesspp::Board::populateDefaultBoard(void) {
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

/**
 * Cleans chess board.
 **/
void chesspp::Board::cleanBoard(void) {
  for (int j = 0; j < 8; j++) {
    for (int i = 0; i < 8; i++) {
      state[j][i].RemovePiece();
    }
  }
}

chesspp::Square &chesspp::Board::at(char col, int row) {
  int j(int(col - 97)), i(row - 1);
  return state[j][i];
}
