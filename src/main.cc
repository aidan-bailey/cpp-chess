#include "chess-board/Board.h"
#include <iostream>
#include <utility>

int main(int argc, char *argv[]) {
  chesspp::Board board;
  std::cout << board.toString() << std::endl;
  return 0;
}
