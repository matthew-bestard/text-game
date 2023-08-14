#include "player.h"
#include "level.h"
#include <stdlib.h>
#include <curses.h>
#include "game.h"

/* Implementations of functions declared in player.h */
Player *playerSetup(Level *newLevel) {
  Player *newPlayer; // creates a variable that will hold the yet uncreated new player of the struct type Player
  newPlayer = malloc(sizeof(Player)); // allocates enough memory to hold a player of type struct Player
  newPlayer->position.x = 14; // sets starting x position in newPlayer x position member
  newPlayer->position.y = 14; // sets starting x position in newPlayer y position member
  newPlayer->health = 20; // sets player starting health
  playerMove(16, 16, newPlayer, newLevel); // player start position
  return newPlayer;
}

