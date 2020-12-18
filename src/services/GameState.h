#ifndef __GAMESTATE_H_
#define __GAMESTATE_H_

namespace chesspp {
enum GameState { BlackVictory, WhiteVictory, Draw, Playing };
static const char *GameStateNames[] = {"Black Victory", "White Victory", "Draw",
                                       "Playing"};
} // namespace chesspp

#endif // __GAMESTATE_H_
