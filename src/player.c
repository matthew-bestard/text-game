#include <stdlib.h>
#include <curses.h>
#include "player.h"
#include "level.h"
#include "game.h"

/* Implementations of functions declared in player.h */
Player *playerSetup(Level *newLevel) {
  Player *newPlayer = malloc(sizeof(Player));
  if (newPlayer == NULL) {
    return NULL;
  }

  newPlayer->position.x = 14; // sets starting x position in newPlayer x position member
  newPlayer->position.y = 14; // sets starting x position in newPlayer y position member
  newPlayer->health = 20; // sets player starting health
  playerMove(16, 16, newPlayer, newLevel); // player start position

  return newPlayer;
}
