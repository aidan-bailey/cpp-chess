#ifndef __SQUARE_H_
#define __SQUARE_H_

#include "ChessColour.h"
#include "SquareType.h"

namespace models {

struct Square {
  enums::SquareType Type;
  enums::ChessColour Colour;
  Square(enums::SquareType type, enums::ChessColour colour);
};

} // namespace models

#endif // __SQUARE_H_
