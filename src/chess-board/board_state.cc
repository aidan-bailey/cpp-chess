#include "board_state.h"
#include "square_location.h"

chesspp::BoardState::BoardState(void) {
  for (char col = 'a'; col < 'h' + 1; col++) {
    for (int row = 1; row < 8 + 1; row++) {
      const Square square = Square(SquareLocation({col, row}));
      squares[col - 97][row - 1] = square;
    }
  }
}
