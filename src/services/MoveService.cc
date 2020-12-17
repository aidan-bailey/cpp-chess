#include "MoveService.h"
#include "Square.h"
#include <utility>

chesspp::MoveService::MoveService(ChessColour &player, Board &brd)
    : to_play(player), board(brd) {}

const std::vector<chesspp::Turn> chesspp::MoveService::GetAvailableTurns(void) {
  std::vector<Turn> result;
  for (char col = 'a'; col < 'h' + 1; col++) {
    for (int row = 1; row < 8 + 1; row++) {
      Square &square = board.At(col, row);
      if (!square.IsOccuppied() || square.GetPiece().Colour != to_play) {
        continue;
      }
      std::pair<char, int> source{col, row};
      switch (square.GetPiece().Type) {
      case King:
        break;
      case Queen:
        break;
      case Bishop:
        break;
      case Knight:
        break;
      case Rook:
        lanes(source, result);
        break;
      case Pawn:
        step(source, result);
        double_step(source, result);
        break;
      }
    }
  }
  return result;
}

bool isValid(char col, int row) {
  return !(col < 'a' || col > 'h' || row < 1 || row > 8);
}

void chesspp::MoveService::step(std::pair<char, int> &location,
                                std::vector<chesspp::Turn> &current) {
  int direction = to_play == White ? 1 : -1;
  char src_col = location.first;
  int trg_row = location.second + direction;
  // middle
  if (!isValid(src_col, trg_row))
    return;
  if (!board.At(src_col, trg_row).IsOccuppied())
    current.emplace_back(Turn{location, std::make_pair(src_col, trg_row)});
  // left + right
  for (int i = -1; i < 3; i += 2) {
    if (isValid(src_col + i, trg_row)) {
      Square &square = board.At(src_col + i, trg_row);
      if (square.IsOccuppied() && square.GetPiece().Colour != to_play)
        current.emplace_back(
            Turn{location, std::make_pair(src_col + i, trg_row)});
    }
  }
};

void chesspp::MoveService::double_step(std::pair<char, int> &location,
                                       std::vector<chesspp::Turn> &current) {
  switch (to_play) {
  case White:
    if (location.second != 2)
      return;
    break;
  case Black:
    if (location.second != 7)
      return;
    break;
  }
  int direction = to_play == White ? 2 : -2;
  char src_col = location.first;
  int trg_row = location.second + direction;
  // middle
  if (!isValid(src_col, trg_row))
    return;
  if (!board.At(src_col, trg_row).IsOccuppied())
    current.emplace_back(Turn{location, std::make_pair(src_col, trg_row)});
};

void chesspp::MoveService::lanes(std::pair<char, int> &location,
                                 std::vector<chesspp::Turn> &current) {
  char src_col = location.first;
  int src_row = location.second;
  // up
  for (int trg_row = src_row + 1; trg_row < 9; trg_row++) {
    if (!isValid(src_col, trg_row))
      break;
    Square &square = board.At(src_col, trg_row);
    if (!square.IsOccuppied()) {
      current.emplace_back(Turn{location, std::make_pair(src_col, trg_row)});
      continue;
    }
    if (square.GetPiece().Colour != to_play) {
      current.emplace_back(Turn{location, std::make_pair(src_col, trg_row)});
    }
    break;
  }
  // down
  for (int trg_row = src_row - 1; trg_row > 0; trg_row--) {
    if (!isValid(src_col, trg_row))
      break;
    Square &square = board.At(src_col, trg_row);
    if (!square.IsOccuppied()) {
      current.emplace_back(Turn{location, std::make_pair(src_col, trg_row)});
      continue;
    }
    if (square.GetPiece().Colour != to_play) {
      current.emplace_back(Turn{location, std::make_pair(src_col, trg_row)});
    }
    break;
  }
  // left
  for (int trg_col = src_col - 1; trg_col > 'a' - 1; trg_col--) {
    if (!isValid(trg_col, src_row))
      break;
    Square &square = board.At(trg_col, src_row);
    if (!square.IsOccuppied()) {
      current.emplace_back(Turn{location, std::make_pair(trg_col, src_row)});
      continue;
    }
    if (square.GetPiece().Colour != to_play) {
      current.emplace_back(Turn{location, std::make_pair(trg_col, src_row)});
    }
    break;
  }
  // right
  for (int trg_col = src_col + 1; trg_col < 'h' + 1; trg_col++) {
    if (!isValid(trg_col, src_row))
      break;
    Square &square = board.At(trg_col, src_row);
    if (!square.IsOccuppied()) {
      current.emplace_back(Turn{location, std::make_pair(trg_col, src_row)});
      continue;
    }
    if (square.GetPiece().Colour != to_play) {
      current.emplace_back(Turn{location, std::make_pair(trg_col, src_row)});
    }
    break;
  }
};

void chesspp::MoveService::diags(std::pair<char, int> &location,
                                 std::vector<chesspp::Turn> &current){
    // TODO
};

void chesspp::MoveService::kings_walk(std::pair<char, int> &location,
                                      std::vector<chesspp::Turn> &current){
    // TODO
};

void chesspp::MoveService::jump(std::pair<char, int> &location,
                                std::vector<chesspp::Turn> &current){
    // TODO
};
