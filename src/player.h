#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "level.h"

typedef struct Player { // defines a struct for Players 
  Position position;
  int health;
  int attack;
  int defense;
} Player;

Player *playerSetup(Level * newLevel);

#endif	/* PLAYER_H */
