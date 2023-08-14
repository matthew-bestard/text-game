#ifndef GAME_H
#define GAME_H

#include "level.h"
#include "player.h"
#include "monster.h"

/* Function prototypes for the main game logic */
void handleInput(int input, Player *user, Level *newLevel);
void checkPosition(int newY, int newX, Player * user, Level * newLevel);
void playerMove(int y, int x, Player *user, Level *newLevel);

#endif /* GAME_H */
