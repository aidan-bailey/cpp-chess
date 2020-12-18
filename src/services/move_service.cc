#include "move_service.h"
#include "square.h"
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
        kings_walk(source, result);
        break;
      case Queen:
        lanes(source, result);
        diags(source, result);
        break;
      case Bishop:
        diags(source, result);
        break;
      case Knight:
        jump(source, result);
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
                                 std::vector<chesspp::Turn> &current) {
  const char src_col = location.first;
  const int src_row = location.second;
  for (int y = -1; y < 2; y += 2)
    for (int x = -1; x < 2; x += 2)
      for (char j = src_col + x, i = src_row + y; isValid(j, i);
           i += y, j += x) {
        Square &square = board.At(j, i);
        if (!square.IsOccuppied()) {
          current.emplace_back(Turn{location, std::make_pair(j, i)});
          continue;
        }
        if (square.GetPiece().Colour != to_play) {
          current.emplace_back(Turn{location, std::make_pair(j, i)});
        }
        break;
      }
};

void chesspp::MoveService::kings_walk(std::pair<char, int> &location,
                                      std::vector<chesspp::Turn> &current) {
  const char src_col = location.first;
  const int src_row = location.second;
  // top
  for (int i = src_row - 1; i < src_row + 1 + 1; i++)
    for (char j = src_col - 1; j < src_col + 1 + 1; j++) {
      if (!isValid(j, i) || std::make_pair(j, i) == location)
        continue;
      Square &square = board.At(j, i);
      if (!square.IsOccuppied()) {
        current.emplace_back(Turn{location, std::make_pair(j, i)});
        continue;
      }
      if (square.GetPiece().Colour != to_play) {
        current.emplace_back(Turn{location, std::make_pair(j, i)});
      }
    }
};

void chesspp::MoveService::jump(std::pair<char, int> &location,
                                std::vector<chesspp::Turn> &current) {
  const char src_col = location.first;
  const int src_row = location.second;
  for (int x = 1; x > -2; x -= 2)
    for (int y = 1; y > -2; y -= 2) {
      // middle
      char j = src_col + x * 2;
      int i = src_row + y * 1;
      if (isValid(j, i)) {
        Square &square = board.At(j, i);
        if (!square.IsOccuppied() || square.GetPiece().Colour != to_play) {
          current.emplace_back(Turn{location, std::make_pair(j, i)});
        }
      }
      // top
      j = src_col + x * 1;
      i = src_row + y * 2;
      if (isValid(j, i)) {
        Square &square = board.At(j, i);
        if (!square.IsOccuppied() || square.GetPiece().Colour != to_play) {
          current.emplace_back(Turn{location, std::make_pair(j, i)});
        }
      }
    }
}
