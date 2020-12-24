#ifndef __GAME_STATE_H_
#define __GAME_STATE_H_

namespace chesspp {
enum GameState { BlackVictory, WhiteVictory, Stalemate, Playing };
static const char *GameStateNames[] = {"Black Victory", "White Victory",
                                       "Stalemate", "Playing"};
} // namespace chesspp

#endif // __GAMESTATE_H_
