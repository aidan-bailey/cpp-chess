#include "move_utility.h"
#include "chess_colour.h"
#include "linear_search.hpp"
#include "piece_type.h"
#include "square.h"
#include "square_location.h"
#include "turn.h"
#include <algorithm>
#include <utility>
#include <vector>

std::vector<chesspp::Turn>
chesspp::MoveUtility::GetAvailableTurns(const Board &board, ChessColour to_play,
                                        const std::vector<Turn> turn_history) {
  std::vector<Turn> result(getAllAvailableTurns(board, to_play, turn_history));
  removeIllegals(board, to_play, result, turn_history);
  return result;
}

std::vector<chesspp::Turn> chesspp::MoveUtility::getAllAvailableTurns(
    const Board &board, ChessColour to_play, const std::vector<Turn> &history) {
  std::vector<Turn> result;
  for (char col = 'a'; col < 'h' + 1; col++) {
    for (int row = 1; row < 8 + 1; row++) {
      const Square &square = board.At(SquareLocation{col, row});
      if (!square.IsOccuppied() || square.GetPiece().Colour != to_play) {
        continue;
      }
      SquareLocation source{col, row};
      std::vector<Turn> moves;
      switch (square.GetPiece().Type) {
      case King:
        moves = kings_walk(board, to_play, source);
        result.insert(result.end(), moves.begin(), moves.end());
        break;
      case Queen:
        moves = lanes(board, to_play, source);
        result.insert(result.end(), moves.begin(), moves.end());
        moves = diags(board, to_play, source);
        result.insert(result.end(), moves.begin(), moves.end());
        break;
      case Bishop:
        moves = diags(board, to_play, source);
        result.insert(result.end(), moves.begin(), moves.end());
        break;
      case Knight:
        moves = jump(board, to_play, source);
        result.insert(result.end(), moves.begin(), moves.end());
        break;
      case Rook:
        moves = lanes(board, to_play, source);
        result.insert(result.end(), moves.begin(), moves.end());
        break;
      case Pawn:
        moves = step(board, to_play, source);
        result.insert(result.end(), moves.begin(), moves.end());
        moves = double_step(board, to_play, source);
        result.insert(result.end(), moves.begin(), moves.end());
        break;
      }
    }
  }
  return result;
}

bool chesspp::MoveUtility::isValid(char col, int row) {
  return !(col < 'a' || col > 'h' || row < 1 || row > 8);
}

std::vector<chesspp::Turn> chesspp::MoveUtility::step(const Board &board,
                                                      ChessColour to_play,
                                                      SquareLocation location) {
  std::vector<Turn> result;
  int direction = to_play == White ? 1 : -1;
  char src_col = location.col;
  int trg_row = location.row + direction;
  // middle
  if (!isValid(src_col, trg_row))
    return result;
  if (!board.At(SquareLocation{src_col, trg_row}).IsOccuppied())
    result.emplace_back(Turn{location, SquareLocation{src_col, trg_row}});
  // left + right
  for (int i = -1; i < 3; i += 2) {
    if (isValid(src_col + i, trg_row)) {
      const Square &square =
          board.At(SquareLocation{char(src_col + i), trg_row});
      if (square.IsOccuppied() && square.GetPiece().Colour != to_play)
        result.emplace_back(
            Turn{location, SquareLocation{char(src_col + i), trg_row}});
    }
  }
  return result;
};

std::vector<chesspp::Turn>
chesspp::MoveUtility::double_step(const Board &board, ChessColour to_play,
                                  SquareLocation location) {
  std::vector<Turn> result;
  switch (to_play) {
  case White:
    if (location.row != 2)
      return result;
    break;
  case Black:
    if (location.row != 7)
      return result;
    break;
  }
  int direction = to_play == White ? 2 : -2;
  char src_col = location.col;
  int trg_row = location.row + direction;
  // middle
  if (!isValid(src_col, trg_row))
    return result;
  if (!board.At(SquareLocation{src_col, trg_row}).IsOccuppied())
    result.emplace_back(Turn{location, SquareLocation{src_col, trg_row}});
  return result;
};

std::vector<chesspp::Turn>
chesspp::MoveUtility::lanes(const Board &board, ChessColour to_play,
                            SquareLocation location) {
  std::vector<Turn> result;
  char src_col = location.col;
  int src_row = location.row;
  // up
  for (int trg_row = src_row + 1; trg_row < 9; trg_row++) {
    if (!isValid(src_col, trg_row))
      break;
    const Square &square = board.At(SquareLocation{src_col, trg_row});
    if (!square.IsOccuppied()) {
      result.emplace_back(Turn{location, SquareLocation{src_col, trg_row}});
      continue;
    }
    if (square.GetPiece().Colour != to_play) {
      result.emplace_back(Turn{location, SquareLocation{src_col, trg_row}});
    }
    break;
  }
  // down
  for (int trg_row = src_row - 1; trg_row > 0; trg_row--) {
    if (!isValid(src_col, trg_row))
      break;
    const Square &square = board.At(SquareLocation{src_col, trg_row});
    if (!square.IsOccuppied()) {
      result.emplace_back(Turn{location, SquareLocation{src_col, trg_row}});
      continue;
    }
    if (square.GetPiece().Colour != to_play) {
      result.emplace_back(Turn{location, SquareLocation{src_col, trg_row}});
    }
    break;
  }
  // left
  for (char trg_col = src_col - 1; trg_col > 'a' - 1; trg_col--) {
    if (!isValid(trg_col, src_row))
      break;
    const Square &square = board.At(SquareLocation{trg_col, src_row});
    if (!square.IsOccuppied()) {
      result.emplace_back(
          Turn{location, SquareLocation{char(trg_col), src_row}});
      continue;
    }
    if (square.GetPiece().Colour != to_play) {
      result.emplace_back(
          Turn{location, SquareLocation{char(trg_col), src_row}});
    }
    break;
  }
  // right
  for (char trg_col = src_col + 1; trg_col < 'h' + 1; trg_col++) {
    if (!isValid(trg_col, src_row))
      break;
    const Square &square = board.At(SquareLocation{trg_col, src_row});
    if (!square.IsOccuppied()) {
      result.emplace_back(
          Turn{location, SquareLocation{char(trg_col), src_row}});
      continue;
    }
    if (square.GetPiece().Colour != to_play) {
      result.emplace_back(
          Turn{location, SquareLocation{char(trg_col), src_row}});
    }
    break;
  }
  return result;
};

std::vector<chesspp::Turn>
chesspp::MoveUtility::diags(const Board &board, ChessColour to_play,
                            SquareLocation location) {
  std::vector<Turn> result;
  const char src_col = location.col;
  const int src_row = location.row;
  for (int y = -1; y < 2; y += 2)
    for (int x = -1; x < 2; x += 2)
      for (char j = src_col + x, i = src_row + y; isValid(j, i);
           i += y, j += x) {
        const Square &square = board.At(SquareLocation{j, i});
        if (!square.IsOccuppied()) {
          result.emplace_back(Turn{location, SquareLocation{j, i}});
          continue;
        }
        if (square.GetPiece().Colour != to_play) {
          result.emplace_back(Turn{location, SquareLocation{j, i}});
        }
        break;
      }
  return result;
};

std::vector<chesspp::Turn>
chesspp::MoveUtility::kings_walk(const Board &board, ChessColour to_play,
                                 SquareLocation location) {
  std::vector<Turn> result;
  const char src_col = location.col;
  const int src_row = location.row;
  // top
  for (int i = src_row - 1; i < src_row + 1 + 1; i++)
    for (char j = src_col - 1; j < src_col + 1 + 1; j++) {
      if (!isValid(j, i) || i == src_row && j == src_col)
        continue;
      const Square &square = board.At(SquareLocation{j, i});
      if (!square.IsOccuppied()) {
        result.emplace_back(Turn{location, SquareLocation{j, i}});
        continue;
      }
      if (square.GetPiece().Colour != to_play) {
        result.emplace_back(Turn{location, SquareLocation{j, i}});
      }
    }
  return result;
};

std::vector<chesspp::Turn> chesspp::MoveUtility::jump(const Board &board,
                                                      ChessColour to_play,
                                                      SquareLocation location) {
  std::vector<Turn> result;
  const char src_col = location.col;
  const int src_row = location.row;
  for (int x = 1; x > -2; x -= 2)
    for (int y = 1; y > -2; y -= 2) {
      // middle
      char j = src_col + x * 2;
      int i = src_row + y * 1;
      if (isValid(j, i)) {
        const Square &square = board.At(SquareLocation{j, i});
        if (!square.IsOccuppied() || square.GetPiece().Colour != to_play) {
          result.emplace_back(Turn{location, SquareLocation{j, i}});
        }
      }
      // top
      j = src_col + x * 1;
      i = src_row + y * 2;
      if (isValid(j, i)) {
        const Square &square = board.At(SquareLocation{j, i});
        if (!square.IsOccuppied() || square.GetPiece().Colour != to_play) {
          result.emplace_back(Turn{location, SquareLocation{j, i}});
        }
      }
    }
  return result;
}

void chesspp::MoveUtility::removeIllegals(const Board &board,
                                          ChessColour to_play,
                                          std::vector<Turn> &currentTurns,
                                          std::vector<Turn> history) {
  // find king
  int king_row(-1);
  char king_char(-1);
  for (int row = 1; row < 8 + 1; row++) {
    for (char col = 'a'; col < 'h' + 1; col++) {
      const Square &square = board.At(SquareLocation{col, row});
      if (!square.IsOccuppied() || square.GetPiece().Type != King ||
          square.GetPiece().Colour != to_play) {
        continue;
      }
      king_row = row;
      king_char = col;
      break;
    }
  }
  if (!isValid(king_char, king_row))
    return;
  SquareLocation king_location{king_char, king_row};
  // simulate every move
  std::vector<Turn> illegalMoves;
  for (auto turn : currentTurns) {
    Board board_copy(board);
    board_copy.MakeMove(turn.From, turn.To);
    auto next_turns = getAllAvailableTurns(
        board_copy, to_play == White ? Black : White, history);
    for (auto next_turn : next_turns) {
      Board board_copy_copy(board_copy);
      board_copy_copy.MakeMove(next_turn.From, next_turn.To);
      if (next_turn.To == king_location) {
        illegalMoves.emplace_back(turn);
        break;
      }
    }
  }
  for (auto illegal_turn : illegalMoves) {
    int index = search::linear_search(illegal_turn, &currentTurns[0],
                                      currentTurns.size());
    currentTurns.erase(currentTurns.begin() + index);
  }
}
